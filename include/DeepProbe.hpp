#ifndef DEEP_PROBE_HPP
#define DEEP_PROBE_HPP

#include "DFS.hpp"
#include <vector>

class DeepProbe {
private:
    const std::vector<std::vector<int>>& graph; 
    int maxDepth;
    DFS dfs;

    void dfsLimited(int current, int target, int depth,
                    std::vector<bool>& visited, std::vector<int>& path,
                    std::vector<std::vector<int>>& allPaths);

public:
    DeepProbe(const std::vector<std::vector<int>>& adjacencyMatrix, int depthLimit = 3);
    void probe(int start, int end);
    std::vector<std::vector<int>> getAllPaths(int start, int end);
       
};

#endif

