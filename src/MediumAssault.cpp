#include "MediumAssault.hpp"
#include <iostream>
#include <algorithm>
#include <limits>

MediumAssault::MediumAssault(const std::vector<std::vector<int>>& graph, int depthLimit)
    : graph(graph), maxDepth(depthLimit), probe(graph, depthLimit) {}

int MediumAssault::calculatePathCost(const std::vector<int>& path) const {
    int cost = 0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        cost += graph[path[i]][path[i + 1]];
    }
    return cost;
}

std::vector<int> MediumAssault::twoOptSwap(const std::vector<int>& path, int i, int k) const {
    std::vector<int> newPath;
    newPath.insert(newPath.end(), path.begin(), path.begin() + i);
    std::vector<int> reversed(path.begin() + i, path.begin() + k + 1);
    std::reverse(reversed.begin(), reversed.end());
    newPath.insert(newPath.end(), reversed.begin(), reversed.end());
    newPath.insert(newPath.end(), path.begin() + k + 1, path.end());
    return newPath;
}

std::vector<int> MediumAssault::findBestPath(const std::vector<std::vector<int>>& paths) {
    if (paths.empty()) return {};

    std::vector<int> bestPath = paths[0];
    int bestCost = calculatePathCost(bestPath);

    for (const auto& path : paths) {
        int cost = calculatePathCost(path);
        if (cost < bestCost) {
            bestPath = path;
            bestCost = cost;
        }
    }

    // 2-opt optimization
    bool improved = true;
    while (improved) {
        improved = false;
        for (size_t i = 1; i < bestPath.size() - 2; ++i) {
            for (size_t k = i + 1; k < bestPath.size() - 1; ++k) {
                std::vector<int> newPath = twoOptSwap(bestPath, i, k);
                int newCost = calculatePathCost(newPath);
                if (newCost < bestCost) {
                    bestPath = newPath;
                    bestCost = newCost;
                    improved = true;
                }
            }
        }
    }

    return bestPath;
}

void MediumAssault::optimizeAttackPath(int start, int end) {
    std::cout << "Running DeepProbe from node " << start << " to node " << end << "...\n";

    std::vector<std::vector<int>> allPaths = probe.getAllPaths(start, end);

    if (allPaths.empty()) {
        std::cout << "No paths available from " << start << " to " << end << " within depth " << maxDepth << ".\n";
        return;
    }

    std::vector<int> optimizedPath = findBestPath(allPaths);
    int finalCost = calculatePathCost(optimizedPath);

    std::cout << "Optimized attack path (cost = " << finalCost << "):\n";
    for (size_t i = 0; i < optimizedPath.size(); ++i) {
        std::cout << optimizedPath[i];
        if (i < optimizedPath.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}
