#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;  // City -> (Connected City, Flight Time/Fuel)

    // Add flight path (edge) between two cities
    void addEdge(const string& city1, const string& city2, int cost) {
        adjList[city1].push_back({city2, cost});
        adjList[city2].push_back({city1, cost});  // Since it's an undirected graph
    }

    // DFS to check connectivity
    bool isConnected(const string& startCity) {
        unordered_set<string> visited;
        stack<string> s;
        s.push(startCity);
        
        while (!s.empty()) {
            string city = s.top();
            s.pop();
            if (visited.find(city) == visited.end()) {
                visited.insert(city);
                for (const auto& neighbor : adjList[city]) {
                    if (visited.find(neighbor.first) == visited.end()) {
                        s.push(neighbor.first);
                    }
                }
            }
        }

        // Check if all cities are visited
        return visited.size() == adjList.size();
    }

    // Display the graph (for verification)
    void displayGraph() {
        for (const auto& city : adjList) {
            cout << city.first << ": ";
            for (const auto& neighbor : city.second) {
                cout << neighbor.first << " (" << neighbor.second << " units) ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    g.addEdge("CityA", "CityB", 30);  // Flight from CityA to CityB with time or cost 30 units
    g.addEdge("CityB", "CityC", 45);  // Flight from CityB to CityC with time or cost 45 units
    g.addEdge("CityA", "CityC", 60);  // Flight from CityA to CityC with time or cost 60 units
    g.addEdge("CityC", "CityD", 20);  // Flight from CityC to CityD with time or cost 20 units

    // Display the graph (adjacency list)
    cout << "Graph representation (Adjacency List):" << endl;
    g.displayGraph();

    // Check if the graph is connected
    if (g.isConnected("CityA")) {
        cout << "The graph is connected." << endl;
    } else {
        cout << "The graph is not connected." << endl;
    }

    return 0;
}
// Output:
// Graph representation (Adjacency List):   
// CityA: CityB (30 units) CityC (60 units)
// CityB: CityA (30 units) CityC (45 units) 
// CityC: CityB (45 units) CityA (60 units) CityD (20 units)
// CityD: CityC (20 units)
// The graph is connected.
// The graph is not connected.
// The output will vary based on the input graph and its connectivity.
// The graph is connected if all cities are reachable from the starting city.
// The output will also depend on the order of edges added and the cities present in the graph.
// The graph is undirected, so the edges are bidirectional.
// The adjacency list representation is used to display the graph.
// The graph is displayed in the format: City: Connected City (Cost)
// The cost can represent time, fuel, or any other metric.