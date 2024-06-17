#include "Kosaraju.hpp"
using namespace std;

void KosarajuList() {
      int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    if (n <= 0 || m <= 0 || m > 2 * n) {
        cout << "Invalid input" << endl;
        return;
    }

    // Use list instead of vector for adjacency lists
    list<list<int>> adj(n), adjT(n);
    cout << "Enter " << m << " edges: " << endl;

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        if (u < 0 || v < 0 || u >= n || v >= n) {
            cout << "Invalid input. There are only " << n << " vertices. Try again." << endl;
            --i;
        } else {
            auto it = next(adj.begin(), u);
            it->push_back(v);
            it = next(adjT.begin(), v);
            it->push_back(u);
            cout << "Edge " << u << " " << v << " added." << endl;
        }
    }

    list<bool> visited(n, false);
    list<int> order;

    function<void(int)> dfs1 = [&](int u) {
        auto itVisited = next(visited.begin(), u);
        *itVisited = true;
        auto itAdj = next(adj.begin(), u);
        for (int v : *itAdj) {
            auto itVVisited = next(visited.begin(), v);
            if (!*itVVisited) {
                dfs1(v);
            }
        }
        order.push_back(u);
    };

    for (int i = 0; i < n; ++i) {
        auto itVisited = next(visited.begin(), i);
        if (!*itVisited) {
            dfs1(i);
        }
    }

    order.reverse(); // Reverse the order directly using list's reverse method
    list<int> component(n, -1);
    list<list<int>> components; // To store the nodes of each component

    function<void(int, list<int>&)> dfs2 = [&](int u, list<int>& comp) {
        auto itComponent = next(component.begin(), u);
        *itComponent = comp.size();
        comp.push_back(u);
        auto itAdjT = next(adjT.begin(), u);
        for (int v : *itAdjT) {
            auto itVComponent = next(component.begin(), v);
            if (*itVComponent == -1) {
                dfs2(v, comp);
            }
        }
    };

    int comp = 0;
    for (int u : order) {
        auto itComponent = next(component.begin(), u);
        if (*itComponent == -1) {
            components.emplace_back(); // Add a new component
            dfs2(u, components.back());
            ++comp;
        }
    }

    cout << "Number of strongly connected components: " << comp << endl;
    int idx = 1;
    for (const auto& comp : components) {
        cout << "Component " << idx++ << ": ";
        for (int node : comp) {
            cout << node << " ";
        }
        cout << endl;
    }
}



