#ifndef MEDIUM_ASSAULT_HPP
#define MEDIUM_ASSAULT_HPP

#include "DeepProbe.hpp"
#include <vector>

class MediumAssault {
private:
    std::vector<std::vector<int>> graph;
    int maxDepth;
    DeepProbe probe;

    std::vector<int> findBestPath(const std::vector<std::vector<int>>& paths);

public:
    MediumAssault(const std::vector<std::vector<int>>& graph, int depthLimit = 3);
    void optimizeAttackPath(int start, int end);
    int calculatePathCost(const std::vector<int>& path) const;
    std::vector<int> twoOptSwap(const std::vector<int>& path, int i, int k) const;
};

#endif
