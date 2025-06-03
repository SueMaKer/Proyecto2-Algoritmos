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
        std::cout << "Nodo " << end << " no es alcanzable desde " << start << ".\n";
        return;
    }

    std::vector<std::vector<int>> allPaths;
    std::vector<int> path;
    std::vector<bool> visited(graph.size(), false);

    dfsLimited(start, end, 0, visited, path, allPaths);

    if (allPaths.empty()) {
        std::cout << "No se encontraron caminos de " << start << " a " << end
                  << " con profundidad máxima de " << maxDepth << ".\n";
    } else {
        std::cout << "Caminos encontrados de " << start << " a " << end
                  << " (profundidad ≤ " << maxDepth << "):\n";
        for (const auto& p : allPaths) {
            for (size_t i = 0; i < p.size(); ++i) {
                std::cout << p[i];
                if (i < p.size() - 1) std::cout << " -> ";
            }
            std::cout << "\n";
        }
        std::cout << "Iteraciones DFS base: " << dfs.getIterationCount() << "\n";
    }
}

// End of DeepProbe.cpp

