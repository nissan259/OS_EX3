#include "Reactor.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <chrono>
#include <thread>

void* handleFd(int fd) {
    char buffer[1024];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Read from fd " << fd << ": " << buffer << std::endl;
    } else if (bytesRead == 0) {
        std::cout << "EOF on fd " << fd << std::endl;
    } else {
        std::cerr << "Error reading from fd " << fd << std::endl;
    }
    return nullptr;
}

int main() {
    void* reactor = Reactor::startReactor();

    // Create two pipes
    int pipefd1[2], pipefd2[2];
    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        std::cerr << "Failed to create pipes" << std::endl;
        return 1;
    }

    // Set the read ends of the pipes to non-blocking
    fcntl(pipefd1[0], F_SETFL, O_NONBLOCK);
    fcntl(pipefd2[0], F_SETFL, O_NONBLOCK);

    // Add the read ends of the pipes to the reactor
    Reactor::addFdToReactor(reactor, pipefd1[0], handleFd);
    Reactor::addFdToReactor(reactor, pipefd2[0], handleFd);

    // Start the reactor in a separate thread
    std::thread reactorThread([reactor]() {
        static_cast<Reactor*>(reactor)->run();
    });

    // Write to the pipes
    std::string message1 = "Hello from pipe 1!";
    std::string message2 = "Greetings from pipe 2!";
    write(pipefd1[1], message1.c_str(), message1.length());
    write(pipefd2[1], message2.c_str(), message2.length());

    // Wait a bit
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Remove one of the file descriptors
    Reactor::removeFdFromReactor(reactor, pipefd1[0]);

    // Write to the pipes again
    std::string message3 = "This should not be read";
    std::string message4 = "This should be read";
    write(pipefd1[1], message3.c_str(), message3.length());
    write(pipefd2[1], message4.c_str(), message4.length());
    std::cout << "Wrote to pipes again" << std::endl;
    // Wait a bit more
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the reactor
    Reactor::stopReactor(reactor);

    // Wait for the reactor thread to finish
    reactorThread.join();
    std::cout << "Reactor thread joined" << std::endl;
    // Close the pipes
    close(pipefd1[0]); close(pipefd1[1]);
    close(pipefd2[0]); close(pipefd2[1]);

    return 0;
}