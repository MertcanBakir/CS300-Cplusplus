#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

// Function to check if the graph is Bipartite
bool isBipartite(vector<vector<int>>& graph, int n, vector<int>& color) {
    for (int start = 1; start <= n; ++start) { // Iterate through all nodes to handle disconnected graphs
        if (color[start] == -1) { // If the node is uncolored, start BFS
            queue<int> q;
            q.push(start);
            color[start] = 0; // Assign the first color (0)

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : graph[node]) { // Traverse all adjacent nodes
                    if (color[neighbor] == -1) { // If the adjacent node is uncolored
                        color[neighbor] = 1 - color[node]; // Assign alternate color
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        return false; // If adjacent node has the same color, it's not bipartite
                    }
                }
            }
        }
    }
    return true; // If no conflicts found, the graph is bipartite
}

// Function to find augmenting paths for maximum matching
bool findMatch(int u, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& match) {
    for (int v : graph[u]) { // Traverse all adjacent nodes
        if (!visited[v]) { // If the node is not yet visited in this DFS
            visited[v] = true;

            // If the node is unmatched or we can find an augmenting path
            if (match[v] == -1 || findMatch(match[v], graph, visited, match)) {
                match[v] = u; // Match node v with node u
                return true;
            }
        }
    }
    return false; // No augmenting path found
}

// Function to calculate the maximum matching in the graph
int maxMatching(vector<vector<int>>& graph, int n, int m) {
    vector<int> match(m + 1, -1); // Array to store matches (-1 means unmatched)
    int result = 0;

    for (int u = 1; u <= n; ++u) { // Iterate through all nodes in the first set
        vector<bool> visited(m + 1, false); // Visited array for this DFS iteration
        if (findMatch(u, graph, visited, match)) { // Find augmenting path for node u
            ++result; // Increment the matching size if a path is found
        }
    }

    return result; // Return the size of the maximum matching
}

int main() {
    string input;
    bool keepRunning = true;

    while (keepRunning) {
        cout << "Enter the graph name (e.g., 'graph1' or 'exit' to terminate): ";
        cin >> input;

        if (input == "exit") {
            keepRunning = false; // Set the control variable to terminate the loop
        } else {
            // Open the file with the given graph name
            string filename = input + ".txt";
            ifstream file(filename);

            if (!file.is_open()) { // Check if the file was successfully opened
                cout << "Error: Could not open file " << filename << endl;
                continue; // Skip to the next iteration if file cannot be opened
            }

            // Read the number of vertices and edges
            int n, m;
            file >> n >> m;

            // Read the edges into the adjacency list
            vector<vector<int>> graph(n + 1); // Adjacency list representation of the graph
            int u, v;
            for (int i = 0; i < m; ++i) {
                file >> u >> v; // Read an edge between u and v
                graph[u].push_back(v); // Add edge u -> v
                graph[v].push_back(u); // Add edge v -> u (since the graph is undirected)
            }
            file.close(); // Close the file after reading all edges

            // Check if the graph is bipartite
            vector<int> color(n + 1, -1); // Color array initialized to -1 (uncolored)
            bool isBipartiteGraph = isBipartite(graph, n, color);

            if (isBipartiteGraph) {
                // Create a bipartite graph for maximum matching
                vector<vector<int>> bipartiteGraph(n + 1);
                for (int u = 1; u <= n; ++u) {
                    if (color[u] == 0) { // Only include edges between different color sets
                        for (int v : graph[u]) {
                            if (color[v] == 1) {
                                bipartiteGraph[u].push_back(v); // Add edge u -> v in bipartite graph
                            }
                        }
                    }
                }

                // Calculate the maximum matching in the bipartite graph
                int maxMatch = maxMatching(bipartiteGraph, n, n);
                cout << "The graph is bipartite." << endl;
                cout << "Maximum matching size: " << maxMatch << endl;
            } else {
                cout << "The graph is not bipartite." << endl;
            }
        }
    }

    return 0;
}