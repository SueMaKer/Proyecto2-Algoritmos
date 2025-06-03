// Pathfinder.hpp
#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class Pathfinder {
public:
    Pathfinder(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph);

    int findShortestPathCost(int start, int end);
    std::vector<int> getShortestPath(int start, int end);

private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
};

#endif // PATHFINDER_HPP

