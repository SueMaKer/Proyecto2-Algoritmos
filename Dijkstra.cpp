#include "Dijkstra.hpp"
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

int dijkstraShortestPathCost(
    const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph,
    int start, int end
) {
    std::unordered_map<int, int> distance;
    for (const auto& [node, _] : graph) {
        distance[node] = std::numeric_limits<int>::max();
    }
    distance[start] = 0;

    using Pair = std::pair<int, int>; // (cost, node)
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentCost, node] = pq.top();
        pq.pop();

        if (node == end) return currentCost;

        for (const auto& [neighbor, weight] : graph.at(node)) {
            int newCost = currentCost + weight;
            if (newCost < distance[neighbor]) {
                distance[neighbor] = newCost;
                pq.push({newCost, neighbor});
            }
        }
    }

    return -1; // No path found
}

std::vector<int> dijkstraShortestPath(
    const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph,
    int start, int end
) {
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> previous;

    for (const auto& [node, _] : graph) {
        distance[node] = std::numeric_limits<int>::max();
    }
    distance[start] = 0;

    using Pair = std::pair<int, int>; // (cost, node)
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentCost, node] = pq.top();
        pq.pop();

        for (const auto& [neighbor, weight] : graph.at(node)) {
            int newCost = currentCost + weight;
            if (newCost < distance[neighbor]) {
                distance[neighbor] = newCost;
                previous[neighbor] = node;
                pq.push({newCost, neighbor});
            }
        }
    }

    std::vector<int> path;
    if (distance[end] == std::numeric_limits<int>::max()) return path;

    for (int node = end; node != start; node = previous[node]) {
        path.push_back(node);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
// This code implements Dijkstra's algorithm to find the shortest path cost and the path itself in a graph.
// It uses a priority queue to efficiently retrieve the next node with the smallest cost.   