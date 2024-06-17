#include "kosaraju-sharir.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

void DFS1List(int v, vector<bool>& visited, list<int>& Stack, const vector<list<int>>& graph) {
    visited[v] = true;
    for (int i : graph[v]) {
        if (!visited[i]) {
            DFS1List(i, visited, Stack, graph);
        }
    }
    Stack.push_front(v); // Simulate stack by pushing to the front of the list
}

void DFS2List(int v, vector<bool>& visited, list<int>& component, const vector<list<int>>& transpose) {
    visited[v] = true;
    component.push_back(v);
    for (int i : transpose[v]) {
        if (!visited[i]) {
            DFS2List(i, visited, component, transpose);
        }
    }
}

vector<vector<int>> findSCCsWithList(const vector<list<int>>& graph, int numVertices) {
    list<int> Stack;
    vector<bool> visited(numVertices, false);
    vector<list<int>> transpose(numVertices);
    vector<vector<int>> SCCs;

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            DFS1List(i, visited, Stack, graph);
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
            list<int> component;
            DFS2List(v, visited, component, transpose);
            vector<int> componentVector(component.begin(), component.end());
            SCCs.push_back(componentVector);
        }
    }

    return SCCs;
}

void runKosarajuSharirWithList() {
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

    vector<list<int>> graph(numVertices);

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

    vector<vector<int>> SCCs = findSCCsWithList(graph, numVertices);

    // Print the SCCs
    cout << "Strongly Connected Components are:\n";
    for (const auto& component : SCCs) {
        for (int v : component)
            cout << v + 1 << " ";  // Adjusting back to 1-based index
        cout << endl;
    }
}
