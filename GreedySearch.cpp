#include "GreedySearch.hpp"
#include <unordered_set>
#include <limits>

GreedySearch::GreedySearch(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph)
    : graph(graph) {}

std::vector<int> GreedySearch::findPath(int start, int target) {
    std::unordered_set<int> visited;
    std::vector<int> path;
    int current = start;

    while (current != target) {
        path.push_back(current);
        visited.insert(current);

        const auto& neighbors = graph[current];
        int minCost = std::numeric_limits<int>::max();
        int nextNode = -1;

        for (const auto& neighbor : neighbors) {
            int node = neighbor.first;
            int cost = neighbor.second;

            if (visited.find(node) == visited.end() && cost < minCost) {
                minCost = cost;
                nextNode = node;
            }
        }

        if (nextNode == -1) {
            // No valid path found
            return {};
        }

        current = nextNode;
    }

    path.push_back(target);
    return path;
}
