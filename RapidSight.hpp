#ifndef RAPIDSIGHT_HPP
#define RAPIDSIGHT_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class RapidSight {
public:
    RapidSight(const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph);
    std::vector<int> getNeighbors(int startNode);

private:
    const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph_;
};

#endif
