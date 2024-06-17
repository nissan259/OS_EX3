#include "kosaraju-sharir.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

void DFS1ListOfLists(int v, vector<bool>& visited, list<int>& Stack, const list<list<int>>& graph, const vector<int>& index_map) {
    visited[v] = true;
    auto it = graph.begin();
    advance(it, index_map[v]);
    for (int i : *it) {
        if (!visited[i]) {
            DFS1ListOfLists(i, visited, Stack, graph, index_map);
        }
    }
    Stack.push_front(v); // Simulate stack by pushing to the front of the list
}

void DFS2ListOfLists(int v, vector<bool>& visited, list<int>& component, const list<list<int>>& transpose, const vector<int>& index_map) {
    visited[v] = true;
    component.push_back(v);
    auto it = transpose.begin();
    advance(it, index_map[v]);
    for (int i : *it) {
        if (!visited[i]) {
            DFS2ListOfLists(i, visited, component, transpose, index_map);
        }
    }
}

vector<vector<int>> findSCCsWithListOfLists(const list<list<int>>& graph, int numVertices) {
    list<int> Stack;
    vector<bool> visited(numVertices, false);
    list<list<int>> transpose(numVertices);
    vector<vector<int>> SCCs;
    vector<int> index_map(numVertices);
    
    int index = 0;
    for (auto it = graph.begin(); it != graph.end(); ++it, ++index) {
        index_map[index] = index;
    }

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            DFS1ListOfLists(i, visited, Stack, graph, index_map);
        }
    }

    // Step 2: Create transpose graph
    for (int v = 0; v < numVertices; v++) {
        auto it = graph.begin();
        advance(it, index_map[v]);
        for (int i : *it) {
            auto transpose_it = transpose.begin();
            advance(transpose_it, index_map[i]);
            transpose_it->push_back(v);
        }
    }

    // Step 3: Process all vertices in order defined by Stack
    fill(visited.begin(), visited.end(), false);
    while (!Stack.empty()) {
        int v = Stack.front();
        Stack.pop_front();

        if (!visited[v]) {
            list<int> component;
            DFS2ListOfLists(v, visited, component, transpose, index_map);
            vector<int> componentVector(component.begin(), component.end());
            SCCs.push_back(componentVector);
        }
    }

    return SCCs;
}

void runKosarajuSharirWithListOfLists() {
    int numVertices, numEdges;

    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    if (numVertices <= 0) {
        cout << "Invalid number of vertices. Must be greater than 0." << endl;
        return;
    }

    cout << "Enter the number of edges: ";
    cin >> numEdges;
    if (numEdges < 0) {
        cout << "Invalid number of edges. Cannot be negative." << endl;
        return;
    }

    list<list<int>> graph(numVertices);

    cout << "Enter " << numEdges << " edges (u v) where 1 <= u, v <= " << numVertices << ":\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 1 || v < 1 || u > numVertices || v > numVertices) {
            cout << "Invalid edge. Vertices must be in the range [1, " << numVertices << "]. Try again." << endl;
            i--; // Decrement i to retry this edge input
        } else {
            auto it = graph.begin();
            advance(it, u - 1);
            it->push_back(v - 1);  // Adjusting for 0-based index
        }
    }

    vector<vector<int>> SCCs = findSCCsWithListOfLists(graph, numVertices);

    // Print the SCCs
    cout << "Strongly Connected Components are:\n";
    for (const auto& component : SCCs) {
        for (int v : component)
            cout << v + 1 << " ";  // Adjusting back to 1-based index
        cout << endl;
    }
}
