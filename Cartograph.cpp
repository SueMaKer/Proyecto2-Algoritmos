#include "Cartograph.hpp"
#include <queue>
#include <limits>
#include <unordered_set>

Cartograph::Cartograph() {
   
}

void Cartograph::setGraph(const std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& costGraph) {
    graph = costGraph;
}

int Cartograph::pathfinder(const std::string& start, const std::string& end) {
    std::unordered_map<std::string, int> distances;
    std::priority_queue<std::pair<int, std::string>,
                        std::vector<std::pair<int, std::string>>,
                        std::greater<>> minHeap;

    for (const auto& node : graph) {
        distances[node.first] = std::numeric_limits<int>::max();
    }

    distances[start] = 0;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        auto [currentDistance, currentNode] = minHeap.top();
        minHeap.pop();

        if (currentNode == end) break;

        for (const auto& neighbor : graph[currentNode]) {
            int newDist = currentDistance + neighbor.second;
            if (newDist < distances[neighbor.first]) {
                distances[neighbor.first] = newDist;
                minHeap.push({newDist, neighbor.first});
            }
        }
    }

    return distances[end];
}

std::unordered_map<std::string, std::unordered_map<std::string, int>> Cartograph::starMapper() {
    // Implementación de Floyd-Warshall
    std::unordered_map<std::string, std::unordered_map<std::string, int>> dist;

    for (const auto& node : graph) {
        for (const auto& neighbor : graph) {
            if (node.first == neighbor.first) {
                dist[node.first][neighbor.first] = 0;
            } else {
                dist[node.first][neighbor.first] = std::numeric_limits<int>::max();
            }
        }
        for (const auto& edge : node.second) {
            dist[node.first][edge.first] = edge.second;
        }
    }

    for (const auto& k : graph) {
        for (const auto& i : graph) {
            for (const auto& j : graph) {
                if (dist[i.first][k.first] != std::numeric_limits<int>::max() &&
                    dist[k.first][j.first] != std::numeric_limits<int>::max()) {
                    dist[i.first][j.first] = std::min(dist[i.first][j.first],
                                                      dist[i.first][k.first] + dist[k.first][j.first]);
                }
            }
        }
    }

    return dist;
}
