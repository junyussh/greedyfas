#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int value;
    Node *next;
};
map<int, Node *> vertex;
// sink affect other nodes' out-degree
void removeSink(vector<vector<int>> &graph, vector<bool> &eliminated, vector<int> &outdegree, int u)
{
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
// source affect other nodes' in-degree
void removeSource(vector<vector<int>> &graph, vector<bool> &eliminated, vector<int> &indegree, int u)
{
    // cout << u << endl;
    for (int v : graph[u])
    {
        indegree[v]--;
    }
}
vector<int> greedyfas(vector<vector<int>> &graph)
{
    const int n = graph.size();
    vector<int> s1, s2;
    vector<int> indegree(n, 0);
    vector<int> outdegree(n, 0);
    vector<bool> eliminated(graph.size(), false);
    int rest = n;
    for (int i = 0; i < n; i++)
    {
        for (int j : graph[i])
        {
            indegree[j]++;
            outdegree[i]++;
        }
    }

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
        if (rest == 0)
        {
            break;
        }

        // if (!has_sink)
        // {
        //     break;
        // }

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
        // if (!has_source)
        // {
        //     break;
        // }
        if (rest == 0)
        {
            break;
        }
        int u_max = -1, delta_max = -1;
        for (int u = 0; u < n; u++)
        {
            if (!eliminated[u])
            {
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

        // int best_sink = -1;
        // int best_source = -1;
        // for (int i = 0; i < n; i++)
        // {
        //     if (!eliminated[i])
        //     {
        //         // find sink node
        //         if (outdegree[i] == 0)
        //         {
        //             s1.push_back(i);
        //             best_sink = i;
        //             eliminated[i] = true;
        //             break;
        //         }
        //     }
        // }
        // for (int i = 0; i < n; i++)
        // {
        //     if (!eliminated[i])
        //     {
        //         // source node
        //         if (indegree[i] == 0)
        //         {
        //             best_source = i;
        //             s2.push_back(i);
        //             eliminated[i] = true;
        //             break;
        //         }
        //     }
        // }
        // // update in-degree
        // for (int i = 0; i < graph[best_sink].size(); ++i)
        // {
        //     int neighbor = graph[best_sink][i];
        //     if (!eliminated[neighbor])
        //     {
        //         indegree[neighbor]--;
        //     }
        // }
    }
    vector<int> s;
    s.insert(s.end(), s1.begin(), s1.end());
    s.insert(s.end(), s2.rbegin(), s2.rend());
    return s;
}
int main(int argc, char const *argv[])
{
    // int n;
    // scanf("%d", &n);
    // for (int i = 0; i < n; i++)
    // {
    //     int v1, v2;
    //     scanf("%d %d", &v1, &v2);
    //     if (vertex.count(v1) == 0)
    //     {
    //         vertex.insert({v1, new Node{v1, NULL}});
    //     }

    // }
    vector<vector<int>> graph = {
        {1},
        {0, 2},
        {3},
        {0, 1}};
    vector<int> fas = greedyfas(graph);
    for (int u : fas)
    {
        cout << u << " -> ";
    }
    cout << endl;

    return 0;
}
