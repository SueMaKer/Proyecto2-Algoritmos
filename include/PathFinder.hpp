#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class Pathfinder {
public:
    Pathfinder(const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph);
    int findShortestPathCost(int startNode, int endNode);

private:
    const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph_;
};

#endif

