#include "kosaraju-sharir.hpp"
#include <iostream>
#include <algorithm>
#include <list>
#include <deque>
#include <vector>


using namespace std;

// List-based implementation
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

// Deque-based implementation
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

// List of lists-based implementation
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

// Vector of vectors-based implementation
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