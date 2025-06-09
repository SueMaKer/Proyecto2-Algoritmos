#include "PathFinder.hpp"
#include <queue>
#include <unordered_map>
#include <limits>

Pathfinder::Pathfinder(const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph)
    : graph_(graph) {}

int Pathfinder::findShortestPathCost(int startNode, int endNode) {
    using pii = std::pair<int,int>; // {cost, node}
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    std::unordered_map<int, int> dist;

    for (const auto& [node, _] : graph_)
        dist[node] = std::numeric_limits<int>::max();

    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [currentCost, currentNode] = pq.top();
        pq.pop();

        if (currentNode == endNode)
            return currentCost;

        if (currentCost > dist[currentNode])
            continue;

        for (const auto& [neighbor, weight] : graph_.at(currentNode)) {
            int newCost = currentCost + weight;
            if (newCost < dist[neighbor]) {
                dist[neighbor] = newCost;
                pq.push({newCost, neighbor});
            }
        }
    }

    return -1; 
}
