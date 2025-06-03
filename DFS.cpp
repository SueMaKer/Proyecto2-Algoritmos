#include "DFS.hpp"

//Constructor for the DFS class
DFS::DFS(const std::vector<std::vector<int>>& matrix, int infinityValue)
    : adjacencyMatrix(matrix), INF(infinityValue), iterations(0) {}

// Runs the DFS algorithm starting from the specified node
void DFS::run(int startNode) {
    int n = adjacencyMatrix.size(); // Get the size of the adjacency matrix
    visited.assign(n, false);
    reachableNodes.clear();
    iterations = 0;
    dfs(startNode);
}

// Recursive DFS function that explores the graph
void DFS::dfs(int node) {
    visited[node] = true;
    reachableNodes.push_back(node);
    ++iterations;

    for (int neighbor = 0; neighbor < adjacencyMatrix.size(); ++neighbor) {
        if (!visited[neighbor] && adjacencyMatrix[node][neighbor] < INF) {
            dfs(neighbor);
        }
    }
}

// Returns a constant reference to the list of reachable nodes
const std::vector<int>& DFS::getReachableNodes() const {
    return reachableNodes;
}

// Returns the number of iterations performed during the DFS
int DFS::getIterationCount() const {
    return iterations;
}

int DFS::getInfinity() const {
    return INF;
}

// End of DFS.cpp

