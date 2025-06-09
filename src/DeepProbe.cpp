#include "DeepProbe.hpp"
#include <iostream>
#include <algorithm>

DeepProbe::DeepProbe(const std::vector<std::vector<int>>& adjacencyMatrix, int depthLimit)
    : graph(adjacencyMatrix), maxDepth(depthLimit), dfs(adjacencyMatrix) {}

void DeepProbe::dfsLimited(int current, int target, int depth, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& allPaths) {
    if (depth > maxDepth) return;

    visited[current] = true;
    path.push_back(current);

    if (current == target) {
        allPaths.push_back(path);
    } else {
        for (int i = 0; i < graph[current].size(); ++i) {
            if (graph[current][i] != 0 && graph[current][i] < dfs.getInfinity() && !visited[i]) {
                dfsLimited(i, target, depth + 1, visited, path, allPaths);
            }
        }
    }

    path.pop_back();
    visited[current] = false;
}

void DeepProbe::probe(int start, int end) {
    dfs.run(start);
    const std::vector<int>& reachable = dfs.getReachableNodes();

    if (std::find(reachable.begin(), reachable.end(), end) == reachable.end()) {
        std::cout << "Node " << end << " is not reachable from " << start << ".\n";
        return;
    }

    std::vector<std::vector<int>> allPaths;
    std::vector<int> path;
    std::vector<bool> visited(graph.size(), false);

    dfsLimited(start, end, -1, visited, path, allPaths);

    if (allPaths.empty()) {
        std::cout << "No paths found from " << start << " to " << end
                  << " within the maximum depth of " << maxDepth << ".\n";
    } else {
        std::cout << "Paths found from " << start << " to " << end
                  << " (depth ≤ " << maxDepth << "):\n";
        for (const auto& p : allPaths) {
            for (size_t i = 0; i < p.size(); ++i) {
                std::cout << p[i];
                if (i < p.size() - 1) std::cout << " -> ";
            }
            std::cout << "\n";
        }
        std::cout << "Base DFS iterations: " << dfs.getIterationCount() << "\n";
    }


}

std::vector<std::vector<int>> DeepProbe::getAllPaths(int start, int end) {
    dfs.run(start);
    const std::vector<int>& reachable = dfs.getReachableNodes();

    std::vector<std::vector<int>> allPaths;
    if (std::find(reachable.begin(), reachable.end(), end) == reachable.end()) {
        return allPaths;  
    }

    std::vector<bool> visited(graph.size(), false);
    std::vector<int> path;

    dfsLimited(start, end, -1, visited, path, allPaths);
    return allPaths;
}




