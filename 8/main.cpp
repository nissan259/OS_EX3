#include <iostream>
#include <pthread.h>
#include "proactor.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

// Sample proactor function
void* handleClient(int sockfd) {
    char buffer[1024];
    std::cout << "Handling client on socket: " << sockfd << std::endl;
    while (true) {
        ssize_t bytesRead = read(sockfd, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0) {
            break; // Connection closed or error
        }
        buffer[bytesRead] = '\0';
        std::cout << "Received from socket " << sockfd << ": " << buffer << std::endl;
        std::string response = "Echo: " + std::string(buffer);
        write(sockfd, response.c_str(), response.size());
        std::cout << "Sent to socket " << sockfd << ": " << response << std::endl;
    }
    close(sockfd);
    std::cout << "Closed socket: " << sockfd << std::endl;
    return NULL;
}

int main() {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(serverFd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Forcefully attaching socket to the port 8080
    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(serverFd);
        exit(EXIT_FAILURE);
    }
    if (listen(serverFd, 3) < 0) {
        perror("listen");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port 8080" << std::endl;

    while (true) {
        if ((newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(serverFd);
            exit(EXIT_FAILURE);
        }
        std::cout << "Accepted new connection, socket: " << newSocket << std::endl;
        pthread_t tid = startProactor(newSocket, handleClient);
        if (tid == -1) {
            std::cerr << "Failed to start proactor for new connection on socket: " << newSocket << std::endl;
            close(newSocket);
        }
    }

    close(serverFd);
    return 0;
}

