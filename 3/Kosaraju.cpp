#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>

using namespace std;

// Define global variables for graph representation
int n = 0, m = 0; // Number of vertices and edges
vector<list<int>> adj; // Adjacency list for the graph
vector<list<int>> adjT; // Transpose adjacency list for Kosaraju's algorithm

// Function to initialize a new graph
void Newgraph(int numVertices, int numEdges) {
    n = numVertices;
    m = numEdges;

    adj.clear();
    adj.resize(n);
    adjT.clear();
    adjT.resize(n);

    cout << "Enter " << m << " edges: " << endl;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u);
        cout << "Edge " << u << " " << v << " added." << endl;
    }
}

// Kosaraju's algorithm function
void Kosaraju() {
    if (n <= 0 || m <= 0 || m > 2 * n) {
        cout << "Invalid input" << endl;
        return;
    }

    vector<bool> visited(n, false);
    list<int> order;

    function<void(int)> dfs1 = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        order.push_back(u);
    };

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    reverse(order.begin(), order.end());
    vector<int> component(n, -1);
    vector<list<int>> components; // To store the nodes of each component

    function<void(int, int)> dfs2 = [&](int u, int comp) {
        component[u] = comp;
        components[comp].push_back(u);
        for (int v : adjT[u]) {
            if (component[v] == -1) {
                dfs2(v, comp);
            }
        }
    };

    int comp = 0;
    for (int u : order) {
        if (component[u] == -1) {
            components.push_back(list<int>()); // Add a new component
            dfs2(u, comp++);
        }
    }

    cout << "Number of strongly connected components: " << comp << endl;
    for (int i = 0; i < comp; ++i) {
        cout << "Component " << i + 1 << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
}

// Function to add a new edge
void Newedge(int u, int v) {
    adj[u].push_back(v);
    adjT[v].push_back(u);
    cout << "Edge " << u << " " << v << " added." << endl;
}

// Function to remove an edge
void Removeedge(int u, int v) {
    auto it = find(adj[u].begin(), adj[u].end(), v);
    if (it != adj[u].end()) {
        adj[u].erase(it);
        cout << "Edge " << u << " " << v << " removed." << endl;
    } else {
        cout << "Edge " << u << " " << v << " does not exist." << endl;
    }

    it = find(adjT[v].begin(), adjT[v].end(), u);
    if (it != adjT[v].end()) {
        adjT[v].erase(it);
    }
}

int main() {
    string command;
    while (true) {
        cin >> command;
        if (command == "Newgraph") {
            int numVertices, numEdges;
            cin >> numVertices >> numEdges;
            Newgraph(numVertices, numEdges);
        } else if (command == "Kosaraju") {
            Kosaraju();
        } else if (command == "Newedge") {
            int u, v;
            cin >> u >> v;
            Newedge(u, v);
        } else if (command == "Removeedge") {
            int u, v;
            cin >> u >> v;
            Removeedge(u, v);
        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
