#include "BFS.hpp"

BFS::BFS(const std::unordered_map<int, std::vector<int>>& graph)
    : graph(graph) {}

std::vector<int> BFS::getNeighbors(int startNode) {
    std::vector<int> neighbors;
    std::unordered_set<int> visited;
    std::queue<int> queue;

    iterations = 0; // Reset
    visited.insert(startNode);
    queue.push(startNode);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        ++iterations;

        for (int neighbor : graph[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                neighbors.push_back(neighbor);
                queue.push(neighbor);
            }
        }
    }

    return neighbors;
}

std::vector<int> BFS::getNeighborsWithTimer(int startNode) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = getNeighbors(startNode);
    auto end = std::chrono::high_resolution_clock::now();
    elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
    return result;
}

int BFS::getIterationCount() const {
    return iterations;
}

double BFS::getElapsedTimeMs() const {
    return elapsedTimeMs;
}