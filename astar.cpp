#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Node {
    int city;
    vector<int> path;
    int cost;
    int f_cost;

    bool operator>(const Node& other) const {
        return f_cost > other.f_cost;
    }
};

// Heuristic function to estimate remaining cost
int heuristic(int city, const vector<int>& path, const vector<vector<int>>& graph) {
    int min_cost = INT_MAX;

    // Iterate over the neighbors of the current city
    for (int neighbor = 0; neighbor < graph[city].size(); ++neighbor) {
        // Check if the neighbor is not in the path
        if (find(path.begin(), path.end(), neighbor) == path.end()) {
            // Update the minimum cost if the neighbor's cost is lower
            min_cost = min(min_cost, graph[city][neighbor]);
        }
    }

    // If there are no neighbors or all neighbors are already in the path, return 0
    return min_cost == INT_MAX ? 0 : min_cost;
}

// A* algorithm for solving TSP
pair<vector<int>, int> a_star_tsp(const vector<vector<int>>& graph, int start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({ start, {start}, 0, heuristic(start, {start}, graph) });

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
                    // Calculate the heuristic value for the new path
                    int f_cost = new_cost + heuristic(next_city, new_path, graph);
                    // Add the new node to the priority queue
                    pq.push({ next_city, new_path, new_cost, f_cost });
                }
            }
        }
    }

    return { best_path, best_cost };
}
