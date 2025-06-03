#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>

int dijkstraShortestPathCost(
    const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph,
    int start, int end
);

std::vector<int> dijkstraShortestPath(
    const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph,
    int start, int end
);

#endif // DIJKSTRA_HPP
