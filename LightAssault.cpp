#include "LightAssault.hpp"
#include <limits>

LightAssault::LightAssault(const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph)
    : graph_(graph) {}

std::vector<int> LightAssault::findGreedyAttackPath(int startNode, int endNode) {
    std::vector<int> path;
    int currentNode = startNode;
    path.push_back(currentNode);

    while (currentNode != endNode) {
        const auto& neighbors = graph_.at(currentNode);
        int nextNode = -1;
        int minCost = std::numeric_limits<int>::max();

        for (const auto& [neighbor, cost] : neighbors) {
            if (cost < minCost) {
                minCost = cost;
                nextNode = neighbor;
            }
        }

        if (nextNode == -1) // no way forward
            break;

        path.push_back(nextNode);
        currentNode = nextNode;
    }

    if (path.back() != endNode)
        path.clear(); // no valid path found

    return path;
}
