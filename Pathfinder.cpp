// Pathfinder.cpp
#include "Pathfinder.hpp"
#include <queue>
#include <climits>
#include <algorithm>  // <-- necesario para std::reverse

Pathfinder::Pathfinder(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph)
    : graph(graph) {}

int Pathfinder::findShortestPathCost(int start, int end) {
    std::unordered_map<int, int> dist;
    for (const auto& pair : graph) {
        dist[pair.first] = INT_MAX;
    }

    dist[start] = 0;
    using PII = std::pair<int, int>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (node == end) {
            return cost;
        }

        for (const auto& neighbor : graph[node]) {
            int next = neighbor.first;
            int edgeCost = neighbor.second;
            if (dist[node] + edgeCost < dist[next]) {
                dist[next] = dist[node] + edgeCost;
                pq.push({dist[next], next});
            }
        }
    }

    return -1; // No path found
}

std::vector<int> Pathfinder::getShortestPath(int start, int end) {
    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;

    for (const auto& pair : graph) {
        dist[pair.first] = INT_MAX;
        prev[pair.first] = -1;
    }

    dist[start] = 0;
    using PII = std::pair<int, int>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        for (const auto& neighbor : graph[node]) {
            int next = neighbor.first;
            int edgeCost = neighbor.second;
            if (dist[node] + edgeCost < dist[next]) {
                dist[next] = dist[node] + edgeCost;
                prev[next] = node;
                pq.push({dist[next], next});
            }
        }
    }

    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    if (path.front() != start) return {}; // No path
    return path;
}
