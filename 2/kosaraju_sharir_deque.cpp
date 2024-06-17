#include "kosaraju-sharir.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

void DFS1Deque(int v, vector<bool>& visited, deque<int>& Stack, const vector<deque<int>>& graph) {
    visited[v] = true;
    for (int i : graph[v]) {
        if (!visited[i]) {
            DFS1Deque(i, visited, Stack, graph);
        }
    }
    Stack.push_front(v); // Simulate stack by pushing to the front of the deque
}

void DFS2Deque(int v, vector<bool>& visited, deque<int>& component, const vector<deque<int>>& transpose) {
    visited[v] = true;
    component.push_back(v);
    for (int i : transpose[v]) {
        if (!visited[i]) {
            DFS2Deque(i, visited, component, transpose);
        }
    }
}

vector<vector<int>> findSCCsWithDeque(const vector<deque<int>>& graph, int numVertices) {
    deque<int> Stack;
    vector<bool> visited(numVertices, false);
    vector<deque<int>> transpose(numVertices);
    vector<vector<int>> SCCs;

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            DFS1Deque(i, visited, Stack, graph);
        }
    }

    // Step 2: Create transpose graph
    for (int v = 0; v < numVertices; v++) {
        for (int i : graph[v]) {
            transpose[i].push_back(v);
        }
    }

    // Step 3: Process all vertices in order defined by Stack
    fill(visited.begin(), visited.end(), false);
    while (!Stack.empty()) {
        int v = Stack.front();
        Stack.pop_front();

        if (!visited[v]) {
            deque<int> component;
            DFS2Deque(v, visited, component, transpose);
            vector<int> componentVector(component.begin(), component.end());
            SCCs.push_back(componentVector);
        }
    }

    return SCCs;
}

void runKosarajuSharirWithDeque() {
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

    vector<deque<int>> graph(numVertices);

    cout << "Enter " << numEdges << " edges (u v) where 1 <= u, v <= " << numVertices << ":\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 1 || v < 1 || u > numVertices || v > numVertices) {
            cout << "Invalid edge. Vertices must be in the range [1, " << numVertices << "]. Try again." << endl;
            i--; // Decrement i to retry this edge input
        } else {
            graph[u - 1].push_back(v - 1);  // Adjusting for 0-based index
        }
    }

    vector<vector<int>> SCCs = findSCCsWithDeque(graph, numVertices);

    // Print the SCCs
    cout << "Strongly Connected Components are:\n";
    for (const auto& component : SCCs) {
        for (int v : component)
            cout << v + 1 << " ";  // Adjusting back to 1-based index
        cout << endl;
    }
}
