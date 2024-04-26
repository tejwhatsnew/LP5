#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

// Define the graph structure (undirected graph)
class Graph
{
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Sequential Breadth First Search
    void sequentialBFS(int source)
    {
        vector<bool> visited(adj.size(), false);
        queue<int> q;
        visited[source] = true;
        q.push(source);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int i = 0; i < adj[u].size(); ++i)
            {
                int v = adj[u][i];
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // Sequential Depth First Search
    void sequentialDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int u = adj[v][i];
            if (!visited[u])
            {
                sequentialDFSUtil(u, visited);
            }
        }
    }

    void sequentialDFS(int source)
    {
        vector<bool> visited(V, false);
        sequentialDFSUtil(source, visited);
    }

    // Parallel Breadth First Search
    void parallelBFS(int source)
    {
       vector<bool> visited(adj.size(), false);
        queue<int> q;
        visited[source] = true;
        q.push(source);
        while (!q.empty())
        {
            int u;
#pragma omp parallel shared(q, visited)
            {
#pragma omp single
                {
                    u = q.front();
                    q.pop();
                    cout << u << " ";
                }
                if (!(adj[u].size() == 0))
                {
#pragma omp for
                    for (int i = 0; i <= adj[u].size() - 1; ++i)
                    {
                        if (!visited[adj[u][i]])
                        {
#pragma omp critical
                            {
                                q.push(adj[u][i]);
                                visited[adj[u][i]] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    // Parallel Depth First Search
    void parallelDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

// Traverse all adjacent vertices
#pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int u = adj[v][i];
            if (!visited[u])
            {
                parallelDFSUtil(u, visited);
            }
        }
    }

    void parallelDFS(int source)
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(source, visited);
    }
};

int main()
{
    int num_vertices, num_edges, source;
    cout << "Enter the number of vertices in the graph: ";
    cin >> num_vertices;
    Graph g(num_vertices);

    cout << "Enter the number of edges in the graph: ";
    cin >> num_edges;

    cout << "Enter the edges (u v): " << endl;
    for (int i = 0; i < num_edges; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> source;

    // Sequential BFS
    auto start = high_resolution_clock::now();
    cout << "Sequential Breadth First Search (BFS) starting from vertex " << source << ": ";
    g.sequentialBFS(source);
    cout << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by sequential BFS: " << duration.count() << " microseconds" << endl;

    // Sequential DFS
    start = high_resolution_clock::now();
    cout << "Sequential Depth First Search (DFS) starting from vertex " << source << ": ";
    g.sequentialDFS(source);
    cout << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by sequential DFS: " << duration.count() << " microseconds" << endl;

    // Parallel BFS
    start = high_resolution_clock::now();
    cout << "Parallel Breadth First Search (BFS) starting from vertex " << source << ": ";
    g.parallelBFS(source);
    cout << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by parallel BFS: " << duration.count() << " microseconds" << endl;

    // Parallel DFS
    start = high_resolution_clock::now();
    cout << "Parallel Depth First Search (DFS) starting from vertex " << source << ": ";
    g.parallelDFS(source);
    cout << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by parallel DFS: " << duration.count() << " microseconds" << endl;

    return 0;
}
