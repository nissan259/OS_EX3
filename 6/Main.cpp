#include "Reactor.hpp"
#include <iostream>
#include <unistd.h>

void* handleFd(int fd) {
    char buffer[1024];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Read from fd " << fd << ": " << buffer << std::endl;
    } else {
        std::cerr << "Error reading from fd " << fd << std::endl;
    }
    return nullptr;
}

int main() {
    void* reactor = Reactor::startReactor();

    int fd = 0; // stdin
    Reactor::addFdToReactor(reactor, fd, handleFd);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    Reactor::stopReactor(reactor);

    return 0;
}
