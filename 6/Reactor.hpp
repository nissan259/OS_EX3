#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <unordered_map>
#include <vector>
#include <functional>
#include <poll.h>
#include <thread>
#include <atomic>
#include <mutex>

using reactorFunc = void* (*)(int fd);

class Reactor {
public:
    Reactor();
    ~Reactor();

    static void* startReactor();
    static int addFdToReactor(void* reactor, int fd, reactorFunc func);
    static int removeFdFromReactor(void* reactor, int fd);
    static int stopReactor(void* reactor);

private:
    void run();

    std::unordered_map<int, reactorFunc> handlers;
    std::vector<struct pollfd> pollfds;
    std::atomic<bool> running;
    std::thread reactorThread;
    std::mutex mtx;
};

#endif // REACTOR_HPP
