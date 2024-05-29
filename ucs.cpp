#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int city;
    vector<int> path;
    int cost;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

// Uniform Cost Search (UCS) algorithm
pair<vector<int>, int> ucs_tsp(const vector<vector<int>>& graph, int start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ start, {start}, 0 });

    int best_cost = INT_MAX;
    vector<int> best_path;

    // Loop until priority queue is empty
    while (!pq.empty()) {
        // Get the current node from the priority queue
        Node current = pq.top();
        pq.pop();

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
                    // Calculate the cost of the new path
                    int new_cost = current.cost + graph[current.city][next_city];
                    // Add the new node to the priority queue
                    pq.push({ next_city, new_path, new_cost });
                }
            }
        }
    }

    return { best_path, best_cost };
}
