#include "RapidSight.hpp"

RapidSight::RapidSight(const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph)
    : graph_(graph) {}

std::vector<int> RapidSight::getNeighbors(int startNode) {
    std::vector<int> neighbors;
    auto it = graph_.find(startNode);
    if (it != graph_.end()) {
        for (const auto& [neighbor, cost] : it->second) {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}
