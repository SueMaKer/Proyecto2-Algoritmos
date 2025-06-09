#include "Probe.hpp"
#include "Config.hpp"
#include <unordered_set>

Probe::Probe() {}

void Probe::setGraph(const std::unordered_map<std::string, std::vector<std::string>>& universeGraph) {
    graph = universeGraph;
}

std::vector<std::string> Probe::rapidSight(const std::string& fromNode) {
    if (graph.find(fromNode) == graph.end()) return {};
    return graph[fromNode];
}

std::vector<std::string> Probe::deepProbe(const std::string& fromNode) {
    std::vector<std::string> result;
    dfsHelper(fromNode, Config::DEFAULT_DFS_DEPTH, result);
    return result;
}

void Probe::dfsHelper(const std::string& node, int depth, std::vector<std::string>& result) {
    if (depth == 0 || graph.find(node) == graph.end()) return;

    for (const auto& neighbor : graph[node]) {
        result.push_back(neighbor);
        dfsHelper(neighbor, depth - 1, result);
    }
}