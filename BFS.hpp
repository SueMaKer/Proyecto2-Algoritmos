#ifndef BFS_HPP
#define BFS_HPP

#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

class BFS {
public:
    BFS(const std::unordered_map<int, std::vector<int>>& graph);
    std::vector<int> getNeighbors(int startNode);

private:
    std::unordered_map<int, std::vector<int>> graph;
};

#endif // BFS_HPP
