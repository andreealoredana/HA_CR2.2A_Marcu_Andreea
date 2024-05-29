#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Function prototypes
pair<vector<int>, int> dfs_tsp(const vector<vector<int>>& graph, int start);
pair<vector<int>, int> ucs_tsp(const vector<vector<int>>& graph, int start);
pair<vector<int>, int> a_star_tsp(const vector<vector<int>>& graph, int start);

// Function to generate a random graph for TSP
vector<vector<int>> generate_random_graph(int N) {
    vector<vector<int>> graph(N, vector<int>(N, 0));

    // Seed the random number generator
    srand(time(nullptr));

    // Generate random distances for the upper triangular part of the matrix
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            graph[i][j] = graph[j][i] = rand() % 100 + 1; // Random distance between 1 and 100
        }
    }

    // Set diagonal elements to 0
    for (int i = 0; i < N; ++i) {
        graph[i][i] = 0;
    }

    return graph;
}

int main() {

    // Define the distance matrix
    /*vector<vector<int>> graph = {
    {0, 25, 30, 35},
    {25, 0, 15, 20},
    {30, 15, 0, 10},
    {35, 20, 10, 0}
    };*/

    int N = 4; // Number of cities
    vector<vector<int>> graph = generate_random_graph(N);

    // Output the generated random graph
    cout << "Graph:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int start = 0;

    // Perform DFS, UCS, and A* algorithms for TSP
    auto dfs_result = dfs_tsp(graph, start);
    cout << "DFS Path: ";
    for (int city : dfs_result.first) {
        cout << city << " ";
    }
    cout << "\nDFS Cost: " << dfs_result.second << "\n";

    auto ucs_result = ucs_tsp(graph, start);
    cout << "UCS Path: ";
    for (int city : ucs_result.first) {
        cout << city << " ";
    }
    cout << "\nUCS Cost: " << ucs_result.second << "\n";

    auto a_star_result = a_star_tsp(graph, start);
    cout << "A* Path: ";
    for (int city : a_star_result.first) {
        cout << city << " ";
    }
    cout << "\nA* Cost: " << a_star_result.second << "\n";

    return 0;
}
