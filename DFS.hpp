#ifndef DFS_HPP
#define DFS_HPP

#include <vector>
#include <chrono>

class DFS {
    private:
        const std::vector<std::vector<int>>& adjacencyMatrix;
        std::vector<bool> visited;
        std::vector<int> reachableNodes;
        int iterations;
        int INF;
        double duration;

        void dfs(int node); // Declaration of the recursive DFS function

    public:
        DFS(const std::vector<std::vector<int>>& matrix, int infinityValue = 1e9);
        void run(int startNode);
        const std::vector<int>& getReachableNodes() const;
        int getIterationCount() const;
        int getInfinity() const;
        void runWithTiming(int startNode);
        double getDuration() const;
};

#endif

