#include "BFS.hpp"

BFS::BFS(const std::unordered_map<int, std::vector<int>>& graph)
    : graph(graph) {}

std::vector<int> BFS::getNeighbors(int startNode) {
    std::vector<int> neighbors;
    std::unordered_set<int> visited;
    std::queue<int> queue;

    visited.insert(startNode);
    queue.push(startNode);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int neighbor : graph[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                neighbors.push_back(neighbor);
                queue.push(neighbor); // Continue exploring deeper
            }
        }
    }

    return neighbors;
}
// This BFS implementation returns all reachable neighbors from the start node
// in a breadth-first manner, exploring all nodes at the present depth prior to moving on to nodes at the next depth level.
// It uses a queue to manage the nodes to explore and a set to track visited nodes,