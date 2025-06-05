#include "Dijkstra.hpp"
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>

// Variables estáticas internas
static int iterationCount = 0;
static double durationMs = 0.0;

int getDijkstraIterationCount() {
    return iterationCount;
}

double getDijkstraDurationMs() {
    return durationMs;
}

int dijkstraShortestPathCost(
    const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph,
    int start, int end
) {
    using namespace std::chrono;
    auto startTime = high_resolution_clock::now();
    iterationCount = 0;

    std::unordered_map<int, int> distance;
    for (const auto& [node, _] : graph) {
        distance[node] = std::numeric_limits<int>::max();
    }
    distance[start] = 0;

    using Pair = std::pair<int, int>; // (cost, node)
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        ++iterationCount;
        auto [currentCost, node] = pq.top();
        pq.pop();

        if (node == end) break;

        for (const auto& [neighbor, weight] : graph.at(node)) {
            int newCost = currentCost + weight;
            if (newCost < distance[neighbor]) {
                distance[neighbor] = newCost;
                pq.push({newCost, neighbor});
            }
        }
    }

    auto endTime = high_resolution_clock::now();
    durationMs = duration_cast<duration<double, std::milli>>(endTime - startTime).count();

    return distance[end] == std::numeric_limits<int>::max() ? -1 : distance[end];
}

std::vector<int> dijkstraShortestPath(
    const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph,
    int start, int end
) {
    using namespace std::chrono;
    auto startTime = high_resolution_clock::now();
    iterationCount = 0;

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
        ++iterationCount;
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

    auto endTime = high_resolution_clock::now();
    durationMs = duration_cast<duration<double, std::milli>>(endTime - startTime).count();

    std::vector<int> path;
    if (distance[end] == std::numeric_limits<int>::max()) return path;

    for (int node = end; node != start; node = previous[node]) {
        path.push_back(node);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}