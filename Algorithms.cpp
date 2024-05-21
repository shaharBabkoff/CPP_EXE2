//id:324207935
//email:shbabkoff123@gmail.com
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <limits>
#include <queue>
#include <algorithm>
#include <climits>
#include <sstream>
#include "Algorithms.hpp"

using namespace std;
namespace Algorithms
{
   

    bool isConnectedHelper(const vector<vector<int>>& graph, size_t node, vector<bool>& visited)
    {
        visited[node] = true;

        for (size_t i = 0; i < graph[node].size(); i++)
        {
            if (graph[node][i] != 0 && !visited[i])
            { // There is an edge and it has not been visited
                isConnectedHelper(graph, i, visited);
            }
        }
        return true;
    }

    bool allVisited(const vector<bool>& visited)
    {
        for (bool v : visited)
        {
            if (!v)
                return false; // If any vertex is not visited, return false
        }
        return true; // All vertices were visited
    }

    bool isConnected(const ariel::Graph &g)
    {
        size_t numVertices = static_cast<size_t>(g.getVerticesNum());
        vector<bool> visited(numVertices, false);

       
        // start from the first vertex only for simplicity
        isConnectedHelper(g.getAdjacenctMat(), 0, visited);

        // Check if all vertices were visited
        return allVisited(visited);
    }

    //uding DFS algorithm
     bool isContainCycleHelper(const vector<vector<int>>& graph, size_t node, vector<bool>& visited,
             vector<bool>& recStack, vector<int>& parent, vector<int>& cycle, bool isDirected)
    {
        visited[node] = true;
        recStack[node] = true;

        for (size_t i = 0; i < graph[node].size(); i++)
        {
            if (graph[node][i] != 0)
            { // There is an edge
                if (!visited[i])
                {
                    parent[i] = static_cast<int>(node);
                    if (isContainCycleHelper(graph, i, visited, recStack, parent, cycle, isDirected))
                    {
                        return true;
                    }
                }
                else if (recStack[i] && (isDirected || static_cast<size_t>(parent[node]) != i))
                {
                    // Cycle detected. Backtrack to print cycle.
                    cycle.push_back(static_cast<int>(i)); 
                    size_t cur = node;
                    while (cur != i)
                    {
                        cycle.push_back(static_cast<int>(cur)); 
                        cur = static_cast<size_t>(parent[cur]);
                    }
                    cycle.push_back(static_cast<int>(i));
                    reverse(cycle.begin(), cycle.end());
                    return true; // Return to stop further DFS
                }
            }
        }

        recStack[node] = false;
        return false;
    }

    bool isContainsCycle(const ariel::Graph &g)
    {
        size_t numVertices = static_cast<size_t>(g.getVerticesNum());
        vector<bool> visited(numVertices, false);
        vector<bool> recStack(numVertices, false);
        vector<int> parent(numVertices, -1);
        vector<int> cycle;

        for (size_t i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                if (isContainCycleHelper(g.getAdjacenctMat(), i, visited, recStack, parent, cycle, g.isDirected()))
                {
                    cout << "The cycle is: ";
                    for (size_t j = 0; j < cycle.size(); j++)
                    {
                        cout << cycle[j];
                        if (j < cycle.size() - 1)
                            cout << "->";
                    }
                    cout << endl;
                    return true;
                }
            }
        }

        cout << "No cycle found." << endl;
        return false;
    }

    string isBipartite(const ariel::Graph &g)
    {
        auto graph = g.getAdjacenctMat();
        const size_t n = g.getVerticesNum();
        vector<int> colors(n, -1); // -1 means uncolored

        vector<int> setA, setB;

        for (size_t start = 0; start < n; ++start)
        {
            if (colors[start] != -1)
            {
                continue; // Skip already colored nodes
            }

            queue<size_t> q;
            q.push(start);
            
            colors[start] = 0; // Start with the first color

            while (!q.empty())
            {
                size_t u = q.front();
                q.pop();

                if (colors[u] == 0)
                {
                    setA.push_back(u);
                }
                else
                {
                    setB.push_back(u);
                }

                for (size_t v = 0; v < n; ++v)
                {
                    if (graph[u][v] != 0)
                    { // There is an edge
                        if (colors[v] == -1)
                        {
                            colors[v] = 1 - colors[u];
                            q.push(v);
                        }
                        else if (colors[v] == colors[u])
                        {
                            return "0"; // Graph is not bipartite
                        }
                    }
                }
            }
        }

        ostringstream output;
        output << "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i)
        {
            output << setA[i];
            if (i < setA.size() - 1)
            {
                output << ", ";
            }
        }
        output << "}, B={";
        for (size_t i = 0; i < setB.size(); ++i)
        {
            output << setB[i];
            if (i < setB.size() - 1)
            {
                output << ", ";
            }
        }
        output << "}";

        return output.str();
    }
    //using bellman ford algorithm
    string shortestPath(const ariel::Graph &graph, int start, int end)
    {
        if (start < 0 || start >= graph.getVerticesNum() || end < 0 || end >= graph.getVerticesNum())
        {
            return "Invalid start or end vertex."; // Error handling
        }

        int V = graph.getVerticesNum();
        vector<int> distance(static_cast<size_t>(V), numeric_limits<int>::max()); 
        vector<int> predecessor(static_cast<size_t>(V), -1);  
        distance[static_cast<size_t>(start)] = 0; 

        // Relaxation process over V-1 iterations
        for (int i = 0; i < V - 1; i++)
        {
            for (int u = 0; u < V; u++)
            {
                for (int v = 0; v < V; v++)
                {
                    int weight = graph.getAdjacenctMat()[u][v];
                    if (weight != 0 && distance[u] != numeric_limits<int>::max() &&
                        distance[u] + weight < distance[v])
                    {
                        distance[v] = distance[u] + weight;
                        predecessor[v] = u;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                int weight = graph.getAdjacenctMat()[u][v];
                if (weight != 0 && distance[u] != numeric_limits<int>::max() &&
                    distance[u] + weight < distance[v])
                {
                    return "-1";
                }
            }
        }

        // Reconstruct the path
        if (distance[end] == numeric_limits<int>::max())
        {
            return "-1";
        }

        vector<int> path;
        for (int at = end; at != -1; at = predecessor[at])
        {
            path.push_back(at);
            if (at == start)
                break;
        }
        reverse(path.begin(), path.end());

        string pathString;
        for (size_t i = 0; i < path.size(); i++)
        {
            if (i > 0)
                pathString += "->";
            pathString += to_string(path[i]);
        }

        return pathString;
    }

string negativeCycle(const ariel::Graph &graph) {
    size_t V = graph.getVerticesNum();
    vector<int> distance(static_cast<size_t>(V), numeric_limits<int>::max());  // Cast V to size_t
    vector<int> predecessor(static_cast<size_t>(V), -1);  // Cast V to size_t
    distance[0] = 0;  // Start from the first vertex

    // Relax all edges V-1 times to find shortest paths
    for (size_t i = 0; i < V - 1; i++) {
        for (size_t u = 0; u < V; u++) {
            for (size_t v = 0; v < V; v++) {
                int weight = graph.getAdjacenctMat()[u][v];
                if (weight != numeric_limits<int>::max() && 
                    distance[u] != numeric_limits<int>::max() &&
                    distance[u] + weight < distance[v] && 
                    weight != 0) {  // Check that there is a valid edge
                    distance[v] = distance[u] + weight;
                    predecessor[v] = static_cast<int>(u);
                }
            }
        }
    }

    // Check for negative weight cycle
    for (size_t u = 0; u < V; u++) {
        for (size_t v = 0; v < V; v++) {
            int weight = graph.getAdjacenctMat()[u][v];
            if (weight != numeric_limits<int>::max() &&
                distance[u] != numeric_limits<int>::max() &&
                distance[u] + weight < distance[v] && 
                weight != 0) {  // Confirm there is a valid edge
                vector<int> cycle;
                int cycle_start = v;
                for (int i = 0; i < V; i++) { // Ensure we are in the cycle
                    cycle_start = predecessor[static_cast<size_t>(cycle_start)];
                }

                // Collect all vertices in the cycle
                int current = cycle_start;
                do {
                    cycle.push_back(current);
                    current = predecessor[static_cast<size_t>(current)];
                } while (current != cycle_start);
                cycle.push_back(cycle_start);  // Complete the cycle

                reverse(cycle.begin(), cycle.end());  // Reverse to start the cycle correctly

                // Constructing the output string
                string cycle_description;
                for (size_t i = 0; i < cycle.size(); ++i) {
                    if (i > 0) cycle_description += " -> ";
                    cycle_description += to_string(cycle[i]);
                }

                return cycle_description;
            }
        }
    }

    return "No negative cycle detected.";
}
  
} // namespace Algorithms
