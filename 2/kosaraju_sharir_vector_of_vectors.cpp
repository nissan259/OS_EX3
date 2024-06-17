#include "kosaraju-sharir.hpp"
#include <iostream>
#include <algorithm>


using namespace std;

void DFS1Vector(int v, vector<bool>& visited, vector<int>& Stack, const vector<vector<int>>& graph) {
    visited[v] = true;
    for (int i : graph[v]) {
        if (!visited[i]) {
            DFS1Vector(i, visited, Stack, graph);
        }
    }
    Stack.push_back(v); // Simulate stack by pushing to the back of the vector
}

void DFS2Vector(int v, vector<bool>& visited, vector<int>& component, const vector<vector<int>>& transpose) {
    visited[v] = true;
    component.push_back(v);
    for (int i : transpose[v]) {
        if (!visited[i]) {
            DFS2Vector(i, visited, component, transpose);
        }
    }
}

vector<vector<int>> findSCCsWithVectorOfVectors(const vector<vector<int>>& graph, int numVertices) {
    vector<int> Stack;
    vector<bool> visited(numVertices, false);
    vector<vector<int>> transpose(numVertices);
    vector<vector<int>> SCCs;

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            DFS1Vector(i, visited, Stack, graph);
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
        int v = Stack.back();
        Stack.pop_back();

        if (!visited[v]) {
            vector<int> component;
            DFS2Vector(v, visited, component, transpose);
            SCCs.push_back(component);
        }
    }

    return SCCs;
}

void runKosarajuSharirWithVectorOfVectors() {
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

    vector<vector<int>> graph(numVertices);

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

    vector<vector<int>> SCCs = findSCCsWithVectorOfVectors(graph, numVertices);

    // Print the SCCs
    cout << "Strongly Connected Components are:\n";
    for (const auto& component : SCCs) {
        for (int v : component)
            cout << v + 1 << " ";  // Adjusting back to 1-based index
        cout << endl;
    }
}
