#ifndef RAPIDSIGHT_HPP
#define RAPIDSIGHT_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class RapidSight {
public:
    RapidSight(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph);

    // Returns the list of neighbors (node, cost) of a given node
    std::vector<std::pair<int, int>> getNeighbors(int node) const;

private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
};

#endif // RAPIDSIGHT_HPP
