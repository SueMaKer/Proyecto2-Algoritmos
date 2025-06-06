#ifndef DFS_HPP
#define DFS_HPP

#include <vector>

class DFS {
private:
    const std::vector<std::vector<int>>& adjacencyMatrix;
    std::vector<bool> visited;
    std::vector<int> reachableNodes;
    int iterations;
    int INF;

    void dfs(int node); // Declaration of the recursive DFS function

public:
    DFS(const std::vector<std::vector<int>>& matrix, int infinityValue = 1e9);

    void run(int startNode);

    const std::vector<int>& getReachableNodes() const;

    int getIterationCount() const;
};

#endif

