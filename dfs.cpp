#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

struct Node {
    int city;
    vector<int> path;
    int cost;
};

// Depth First Search (DFS) algorithm for solving TSP
pair<vector<int>, int> dfs_tsp(const vector<vector<int>>& graph, int start) {
    stack<Node> s;
    s.push({ start, {start}, 0 });

    int best_cost = INT_MAX;
    vector<int> best_path;

    // Loop until stack is empty
    while (!s.empty()) {
        // Get the current node from the top of the stack
        Node current = s.top();
        s.pop();

        // If the current path contains all cities, check if it's better than the best found so far
        if (current.path.size() == graph.size()) {
            int total_cost = current.cost + graph[current.city][start];
            if (total_cost < best_cost) {
                best_cost = total_cost;
                best_path = current.path;
                best_path.push_back(start);
            }
        }
        // If the path is not complete, explore neighbors
        else {
            for (int next_city = 0; next_city < graph.size(); ++next_city) {
                // Check if the city is not already in the path
                if (find(current.path.begin(), current.path.end(), next_city) == current.path.end()) {
                    // Create a new path by adding the next city
                    vector<int> new_path = current.path;
                    new_path.push_back(next_city);
                    // Push the new node onto the stack
                    s.push({ next_city, new_path, current.cost + graph[current.city][next_city] });
                }
            }
        }
    }

    return { best_path, best_cost };
}
