#include "RapidSight.hpp"

RapidSight::RapidSight(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph)
    : graph(graph) {}

std::vector<std::pair<int, int>> RapidSight::getNeighbors(int node) const {
    auto it = graph.find(node);
    if (it != graph.end()) {
        return it->second;
    }
    return {}; // return empty vector if node not found
}
