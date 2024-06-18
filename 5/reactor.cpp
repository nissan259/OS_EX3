//
// Created by guy on 6/18/24.
//
#include "reactor.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>

Reactor::Reactor() : max_fd(-1), running(true) {
    FD_ZERO(&master_set);
    FD_ZERO(&read_set);
    memset(fd_funcs, 0, sizeof(fd_funcs));
}

Reactor::~Reactor() {
    stopReactor();
}

int Reactor::addFdToReactor(int fd, reactorFunc func) {
    if (fd < 0 || fd >= FD_SETSIZE) {
        return -1;
    }
    FD_SET(fd, &master_set);
    if (fd > max_fd) {
        max_fd = fd;
    }
    fd_funcs[fd] = func;
    return 0;
}

int Reactor::removeFdFromReactor(int fd) {
    if (fd < 0 || fd >= FD_SETSIZE) {
        return -1;
    }
    FD_CLR(fd, &master_set);
    if (fd == max_fd) {
        while (max_fd >= 0 && !FD_ISSET(max_fd, &master_set)) {
            max_fd--;
        }
    }
    fd_funcs[fd] = nullptr;
    return 0;
}

void Reactor::stopReactor() {
    running = false;
}

void Reactor::runReactor() {
    while (running) {
        read_set = master_set;
        if (select(max_fd + 1, &read_set, nullptr, nullptr, nullptr) == -1) {
            perror("select");
            exit(1);
        }
        for (int i = 0; i <= max_fd; i++) {
            if (FD_ISSET(i, &read_set) && fd_funcs[i]) {
                fd_funcs[i](i);
            }
        }
    }
}
