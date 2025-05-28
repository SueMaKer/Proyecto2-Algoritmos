#ifndef DFS_HPP
#define DFS_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <set>

class DFS {
public:
    using Graph = std::unordered_map<std::string, std::vector<std::string>>;
    
    DFS(const Graph& graph);
    std::set<std::string> run(const std::string& startNode, int maxDepth = 3);

private:
    const Graph& graph;
    void dfsHelper(const std::string& current, int depth, int maxDepth, std::set<std::string>& visited);
};

#endif

