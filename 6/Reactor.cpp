#include "Reactor.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring> // Include this header for strerror

Reactor::Reactor() : running(false) {}

Reactor::~Reactor() {
    if (running) {
        stopReactor(this);
    }
}

void* Reactor::startReactor() {
    Reactor* reactor = new Reactor();
    reactor->running = true;
    reactor->reactorThread = std::thread(&Reactor::run, reactor);
    return static_cast<void*>(reactor);
}

int Reactor::addFdToReactor(void* reactorPtr, int fd, reactorFunc func) {
    Reactor* reactor = static_cast<Reactor*>(reactorPtr);
    std::lock_guard<std::mutex> lock(reactor->mtx);

    if (reactor->handlers.find(fd) != reactor->handlers.end()) {
        return -1; // fd already exists
    }

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    reactor->pollfds.push_back(pfd);
    reactor->handlers[fd] = func;

    return 0;
}

int Reactor::removeFdFromReactor(void* reactorPtr, int fd) {
    Reactor* reactor = static_cast<Reactor*>(reactorPtr);
    std::lock_guard<std::mutex> lock(reactor->mtx);

    auto it = reactor->handlers.find(fd);
    if (it == reactor->handlers.end()) {
        return -1; // fd not found
    }

    reactor->handlers.erase(it);
    reactor->pollfds.erase(std::remove_if(reactor->pollfds.begin(), reactor->pollfds.end(),
                                          [fd](struct pollfd &pfd) { return pfd.fd == fd; }),
                           reactor->pollfds.end());

    return 0;
}

int Reactor::stopReactor(void* reactorPtr) {
    Reactor* reactor = static_cast<Reactor*>(reactorPtr);
    reactor->running = false;
    if (reactor->reactorThread.joinable()) {
        reactor->reactorThread.join();
    }
    delete reactor;
    return 0;
}

void Reactor::run() {
    while (running) {
        std::vector<struct pollfd> fds_copy;
        {
            std::lock_guard<std::mutex> lock(mtx);
            fds_copy = pollfds;
        }

        int ret = poll(fds_copy.data(), fds_copy.size(), -1);
        if (ret < 0) {
            std::cerr << "Poll error: " << strerror(errno) << std::endl;
            continue;
        }

        for (auto &pfd : fds_copy) {
            if (pfd.revents & POLLIN) {
                std::lock_guard<std::mutex> lock(mtx);
                auto it = handlers.find(pfd.fd);
                if (it != handlers.end()) {
                    it->second(pfd.fd);
                }
            }
        }
    }
}
