#ifndef REACTOR_H
#define REACTOR_H

#include <functional>
#include <sys/select.h>

typedef std::function<void(int)> reactorFunc;

class Reactor {
public:
    Reactor();
    ~Reactor();
    int addFdToReactor(int fd, reactorFunc func);
    int removeFdFromReactor(int fd);
    void stopReactor();
    void runReactor();
private:
    int max_fd;
    fd_set master_set;
    fd_set read_set;
    reactorFunc fd_funcs[FD_SETSIZE];
    bool running;
};

#endif // REACTOR_H
