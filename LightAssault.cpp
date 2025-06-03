#include "LightAssault.hpp"
#include <set>
#include <limits>

LightAssault::LightAssault(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph)
    : graph(graph) {}

std::vector<int> LightAssault::findGreedyAttackPath(int start, int goal) {
    std::set<int> visited;
    std::vector<int> path;
    path.push_back(start);
    int currentNode = start;

    while (currentNode != goal) {
        visited.insert(currentNode);
        const auto& neighbors = graph.at(currentNode);

        int minCost = std::numeric_limits<int>::max();
        int nextNode = -1;

        for (const auto& neighborPair : neighbors) {
            int neighbor = neighborPair.first;
            int cost = neighborPair.second;

            if (visited.find(neighbor) == visited.end() && cost < minCost) {
                minCost = cost;
                nextNode = neighbor;
            }
        }

        if (nextNode == -1) {
            // No more nodes to explore
            return {};
        }

        path.push_back(nextNode);
        currentNode = nextNode;
    }

    return path;
}
