#include "Reactor.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>

#define PORT 9034   // Port we're listening on

using namespace std;

// Global variables for graph representation
int n = 0, m = 0; // Number of vertices and edges
vector<list<int>> adj; // Adjacency list for the graph
vector<list<int>> adjT; // Transpose adjacency list for Kosaraju's algorithm

// Global Reactor pointer
void* g_reactor = nullptr;

// Function prototypes
void* accept_connection(int listener_fd);
void* handle_client(int client_fd);

// Existing graph functions (Newgraph, Kosaraju, Newedge, Removeedge) remain the same

// Signal handler to gracefully shut down the server
void signal_handler(int signum) {
    cout << "Shutting down server..." << endl;
    if (g_reactor) {
        Reactor::stopReactor(g_reactor);
    }
    exit(signum);
}

// Function to handle new connections
void* accept_connection(int listener_fd) {
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int new_fd = accept(listener_fd, (struct sockaddr *)&client_addr, &addrlen);

    if (new_fd == -1) {
        perror("accept");
        return nullptr;
    }

    cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << " on socket " << new_fd << endl;

    // Add the new client socket to the reactor
    Reactor::addFdToReactor(g_reactor, new_fd, handle_client);

    return nullptr;
}

// Function to handle client communication
void* handle_client(int client_fd) {
    char buf[1024];
    int numbytes = recv(client_fd, buf, sizeof(buf) - 1, 0);

    if (numbytes <= 0) {
        if (numbytes == 0) {
            cout << "Client disconnected" << endl;
        } else {
            perror("recv");
        }
        close(client_fd);
        Reactor::removeFdFromReactor(g_reactor, client_fd);
        return nullptr;
    }

    buf[numbytes] = '\0';
    string command(buf);
    stringstream ss(command);
    string cmd;
    ss >> cmd;

    if (cmd == "Newgraph") {
        // Handle Newgraph command
        // ...
    } else if (cmd == "Kosaraju") {
        // Handle Kosaraju command
        // ...
    } else if (cmd == "Newedge") {
        // Handle Newedge command
        // ...
    } else if (cmd == "Removeedge") {
        // Handle Removeedge command
        // ...
    } else if (cmd == "Exit") {
        string msg = "Goodbye!\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
        close(client_fd);
        Reactor::removeFdFromReactor(g_reactor, client_fd);
        return nullptr;
    } else {
        string msg = "Invalid command\n";
        send(client_fd, msg.c_str(), msg.size(), 0);
    }

    return nullptr;
}

int main() {
    int listener;     // Listening socket descriptor
    struct sockaddr_in server_addr;

    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);

    // Create a listening socket
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Set socket options
    int yes = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // Bind the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    memset(&(server_addr.sin_zero), '\0', 8);

    if (bind(listener, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(1);
    }

    cout << "Server is running on port " << PORT << endl;

    // Start the reactor
    g_reactor = Reactor::startReactor();

    // Add the listener socket to the reactor
    Reactor::addFdToReactor(g_reactor, listener, accept_connection);

    // Run the reactor
    static_cast<Reactor*>(g_reactor)->run();

    // This point is reached when the reactor stops
    close(listener);
    cout << "Server shut down" << endl;

    return 0;
}