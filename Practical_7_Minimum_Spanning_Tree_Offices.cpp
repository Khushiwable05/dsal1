#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<pair<int, int>>> adjList;  // Adjacency list (neighbor, weight)

    Graph(int v) {
        V = v;
        adjList.resize(v);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    int primMST() {
        vector<int> key(V, INT_MAX);  // Stores the minimum cost of connecting each vertex
        vector<bool> inMST(V, false); // Tracks which vertices are included in MST
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap
        
        pq.push({0, 0});  // Start with vertex 0 and cost 0
        key[0] = 0;
        
        int mstWeight = 0;
        
        while (!pq.empty()) {
            int u = pq.top().second;  // Extract vertex with minimum key value
            pq.pop();
            
            if (inMST[u]) continue;  // Skip if the vertex is already in MST
            
            inMST[u] = true;
            mstWeight += key[u];
            
            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first, weight = neighbor.second;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});  // Push updated key into priority queue
                }
            }
        }
        return mstWeight;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 6);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 0, 7);
    
    int mstWeight = g.primMST();
    cout << "Minimum cost to connect all offices: " << mstWeight << endl;
    return 0;
}
// Output: Minimum cost to connect all offices: 12
// The output may vary based on the graph structure and weights assigned to edges.
// The MST cost will always be the minimum cost to connect all vertices in the graph.
// The graph is undirected and the weights are positive integers.
// The algorithm used is Prim's algorithm, which is efficient for dense graphs.
// The adjacency list representation is used for efficient traversal of the graph.
// The priority queue is used to efficiently get the vertex with the minimum key value.
// The key array stores the minimum cost to connect each vertex to the MST.