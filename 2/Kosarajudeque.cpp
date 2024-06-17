#include  "Kosaraju.hpp"
using namespace std;


void Kosarajudeque() {
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    if (n <= 0 || m <= 0 || m > 2 * n) {
        cout << "Invalid input" << endl;
        return;
    }

    // Use deque instead of vector for adjacency lists
    deque<deque<int>> adj(n), adjT(n);
    cout << "Enter " << m << " edges: " << endl;

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        if (u < 0 || v < 0 || u >= n || v >= n) {
            cout << "Invalid input. There are only " << n << " vertices. Try again." << endl;
            --i;
        } else {
            adj[u].push_back(v);
            adjT[v].push_back(u);
            cout << "Edge " << u << " " << v << " added." << endl;
        }
    }

    deque<bool> visited(n, false);
    deque<int> order;

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
    deque<int> component(n, -1);
    deque<deque<int>> components; // To store the nodes of each component

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
            components.push_back(deque<int>()); // Add a new component
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