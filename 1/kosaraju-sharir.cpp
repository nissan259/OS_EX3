#include "kosaraju-sharir.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

void DFS1(int v, vector<bool>& visited, stack<int>& Stack, const vector<list<int>>& graph) {
    visited[v] = true;
    for (int i : graph[v]) {
        if (!visited[i]) {
            DFS1(i, visited, Stack, graph);
        }
    }
    Stack.push(v);
}

void DFS2(int v, vector<bool>& visited, vector<int>& component, const vector<list<int>>& transpose) {
    visited[v] = true;
    component.push_back(v);
    for (int i : transpose[v]) {
        if (!visited[i]) {
            DFS2(i, visited, component, transpose);
        }
    }
}

vector<vector<int>> findSCCs(const vector<list<int>>& graph, int numVertices) {
    stack<int> Stack;
    vector<bool> visited(numVertices, false);
    vector<list<int>> transpose(numVertices);
    vector<vector<int>> SCCs;

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            DFS1(i, visited, Stack, graph);
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
        int v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            vector<int> component;
            DFS2(v, visited, component, transpose);
            SCCs.push_back(component);
        }
    }

    return SCCs;
}

void runKosarajuSharir() {
    int numVertices, numEdges;

    // Input validation for number of vertices and edges
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

    vector<vector<int>> SCCs = findSCCs(graph, numVertices);

    // Print the SCCs
    cout << "Strongly Connected Components are:\n";
    for (const auto& component : SCCs) {
        for (int v : component)
            cout << v + 1 << " ";  // Adjusting back to 1-based index
        cout << endl;
    }
}
