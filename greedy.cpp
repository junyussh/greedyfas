#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> greedyfas(const vector<vector<int>>& graph) {
    // Initialize variables
    vector<int> indegrees(graph.size(), 0);
    vector<bool> eliminated(graph.size(), false);
    vector<int> order;

    // Compute in-degrees of all nodes
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            int node = graph[i][j];
            indegrees[node]++;
        }
    }

    // Loop until all nodes have been eliminated
    while (order.size() < graph.size()) {
        // Find the highest-scoring non-eliminated node
        int best_node = -1;
        int best_score = -1;
        for (int i = 0; i < graph.size(); ++i) {
            if (!eliminated[i]) {
                int score = indegrees[i];
                if (score > best_score) {
                    best_node = i;
                    best_score = score;
                }
            }
        }

        // If no non-eliminated nodes remain, break out of the loop
        if (best_node == -1) {
            break;
        }

        // Add the best node to the order and eliminate it from the graph
        order.push_back(best_node);
        eliminated[best_node] = true;
        for (int i = 0; i < graph[best_node].size(); ++i) {
            int neighbor = graph[best_node][i];
            if (!eliminated[neighbor]) {
                indegrees[neighbor]--;
            }
        }
    }

    // If not all nodes were eliminated, return an empty vector
    if (order.size() < graph.size()) {
        return vector<int>();
    }

    // Return the order in which nodes were eliminated
    return order;
}

// Function to find the Feedback Arc Set of a DAG
vector<pair<int, int>> feedback_arc_set(vector<vector<int>>& G) {
    int n = G.size();
    vector<int> in_degree(n, 0), out_degree(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : G[u]) {
            ++in_degree[v];
            ++out_degree[u];
        }
    }
    vector<pair<int, int>> fas;
    vector<bool> removed(n, false);
    while (true) {
        bool has_sink = false;
        for (int u = 0; u < n; ++u) {
            if (!removed[u] && out_degree[u] == 0) {
                has_sink = true;
                removed[u] = true;
                for (int v : G[u]) {
                    --in_degree[v];
                }
            }
        }
        if (!has_sink) {
            break;
        }
        bool has_source = false;
        for (int u = 0; u < n; ++u) {
            if (!removed[u] && in_degree[u] == 0) {
                has_source = true;
                removed[u] = true;
                fas.emplace_back(u, -1);
                for (int v : G[u]) {
                    --out_degree[v];
                }
            }
        }
        if (!has_source) {
            int u_max = -1, delta_max = -1;
            for (int u = 0; u < n; ++u) {
                if (!removed[u]) {
                    int delta = out_degree[u] - in_degree[u];
                    if (delta > delta_max) {
                        delta_max = delta;
                        u_max = u;
                    }
                }
            }
            removed[u_max] = true;
            fas.emplace_back(u_max, -1);
            for (int v : G[u_max]) {
                --out_degree[v];
                --in_degree[u_max];
            }
        }
    }
    reverse(fas.begin(), fas.end());
    return fas;
}

// Driver code
int main() {
    int n = 5;
    vector<vector<int>> G(n);
    G[0] = {1};
    G[1] = {2};
    G[2] = {3};
    G[3] = {};
    G[4] = {2, 3};

    vector<pair<int, int>> fas = feedback_arc_set(G);

    cout << "Feedback Arc Set:\n";
    for (auto [u, v] : fas) {
        if (v == -1) {
            cout << u << " -> ";
        } else {
            cout << "(" << u << ", " << v << ") ";
        }
    }
    cout << endl;

    return 0;
}
