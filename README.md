# greedyfas

## Graph data structure

The graph is stored as adjacency list. This representation is space-efficient for sparse graphs (i.e., graphs with few edges), as it only stores the edges that actually exist in the graph.

In the example below, the graph is stored as a vector of vectors, where `graph[i]` is a vector of integers representing the neighbors of node `i`. 

```cpp
vector<vector<int>> graph = {
        {1, 2},
        {0, 2},
        {0, 1, 3},
        {2}
    };
```

So, if j is in `graph[i]`, it means that there is a directed edge from node `i` to node `j`.

For the example graph, the adjacency list representation would be:

```
Node 0: 1 2 
Node 1: 0 2 
Node 2: 0 1 3 
Node 3: 2 
```



## Build

Just run `make`.
