#include "DFS.hpp"


DFS::DFS(const std::vector<std::vector<int>>& matrix, int infinityValue)
    : adjacencyMatrix(matrix), INF(infinityValue), iterations(0) {}


void DFS::run(int startNode) {
    int n = adjacencyMatrix.size(); 
    visited.assign(n, false);
    reachableNodes.clear();
    iterations = 0;
    dfs(startNode);
}


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


const std::vector<int>& DFS::getReachableNodes() const {
    return reachableNodes;
}


int DFS::getIterationCount() const {
    return iterations;
}

int DFS::getInfinity() const {
    return INF;
}

void DFS::runWithTiming(int startNode) {
    auto start = std::chrono::high_resolution_clock::now(); 
    run(startNode);
    auto end = std::chrono::high_resolution_clock::now(); 
    duration = std::chrono::duration<double, std::milli>(end - start).count(); 
}
double DFS::getDuration() const {
    return duration; 
}


