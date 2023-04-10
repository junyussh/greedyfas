#include <iostream>
#include <vector>
using namespace std;

// Removing the sink affects the out-degree of other nodes
void removeSink(vector<vector<int>> &graph, vector<bool> &eliminated, vector<int> &outdegree, int u)
{
    // Find which node is connected to u
    for (int i = 0; i < (int)graph.size(); i++)
    {
        if (!eliminated[i])
        {
            for (int j : graph[i])
            {
                if (j == u)
                {
                    outdegree[i]--;
                }
            }
        }
    }
}

// Removing the source will affect the in-degree of other nodes
void removeSource(vector<vector<int>> &graph, vector<bool> &eliminated, vector<int> &indegree, int u)
{
    for (int v : graph[u])
    {
        if (!eliminated[v])
        {
            indegree[v]--;
        }
    }
}

vector<int> greedyfas(vector<vector<int>> &graph)
{
    const int n = graph.size();

    vector<int> s1, s2;
    vector<int> indegree(n, 0);
    vector<int> outdegree(n, 0);

    // state of nodes
    vector<bool> eliminated(graph.size(), false);
    // Number of remaining nodes
    int rest = n;

    // compute the in-degree and out-degree of each node
    for (int i = 0; i < n; i++)
    {
        for (int j : graph[i])
        {
            indegree[j]++;
            outdegree[i]++;
        }
    }

    // if the graph is not empty
    while (rest != 0)
    {
        // sink: out-degree == 0
        bool has_sink = false;
        for (int u = 0; u < n; u++)
        {
            if (!eliminated[u] && outdegree[u] == 0)
            {
                has_sink = true;
                eliminated[u] = true;
                s2.push_back(u);
                rest--;
                removeSink(graph, eliminated, outdegree, u);
            }
        }
        // when all nodes are eliminated, exit loop
        if (rest == 0)
        {
            break;
        }

        // source: in-degree == 0
        bool has_source = false;
        for (int u = 0; u < n; u++)
        {
            if (!eliminated[u] && indegree[u] == 0)
            {
                has_source = true;
                eliminated[u] = true;
                s1.push_back(u);
                rest--;
                removeSource(graph, eliminated, indegree, u);
            }
        }
        // when all nodes are eliminated, exit loop
        if (rest == 0)
        {
            break;
        }

        // find the node with maximum δ(u)
        int u_max = -1, delta_max = -1;
        for (int u = 0; u < n; u++)
        {
            if (!eliminated[u])
            {
                // δ(u) = outdegree(u) - indegree(u)
                int delta = outdegree[u] - indegree[u];
                if (delta > delta_max)
                {
                    delta_max = delta;
                    u_max = u;
                }
            }
        }

        s1.push_back(u_max);
        removeSink(graph, eliminated, outdegree, u_max);
        removeSource(graph, eliminated, indegree, u_max);
        eliminated[u_max] = true;
        rest--;
    }

    vector<int> s;
    s.insert(s.end(), s1.begin(), s1.end());
    s.insert(s.end(), s2.rbegin(), s2.rend());

    return s;
}
int main(int argc, char const *argv[])
{
    vector<vector<int>> graph = {
        {1},
        {0, 2},
        {3},
        {0, 1}};

    vector<vector<int>> graph2 = {
        {1, 2},
        {2},
        {3},
        {4, 5, 6},
        {6},
        {4, 7},
        {0},
        {1, 2}
    };

    vector<int> fas = greedyfas(graph);

    for (int u : fas)
    {
        cout << u << " -> ";
    }
    
    cout << endl;

    return 0;
}
