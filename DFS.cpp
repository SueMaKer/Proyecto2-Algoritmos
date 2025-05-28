#include "DFS.hpp"

//Constructor of the DFS class that initializes the graph.
DFS::DFS(const Graph& g) : graph(g) {}

// Runs the DFS algorithm starting from a given node and explores up to a specified depth.
std::set<std::string> DFS::run(const std::string& startNode, int maxDepth) {
    std::set<std::string> visited;
    dfsHelper(startNode, 0, maxDepth, visited);
    return visited;
}

// Helper function for the DFS algorithm that recursively explores the graph.
void DFS::dfsHelper(const std::string& current, int depth, int maxDepth, std::set<std::string>& visited) {
    if (depth > maxDepth || visited.count(current)) return;

    visited.insert(current);

    auto it = graph.find(current);
    if (it != graph.end()) {
        for (const auto& neighbor : it->second) {
            dfsHelper(neighbor, depth + 1, maxDepth, visited);
        }
    }
}

