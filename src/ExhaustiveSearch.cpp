#include "ExhaustiveSearch.hpp"

ExhaustiveSearch::ExhaustiveSearch(const Graph& graph, bool usePruning)
    : graph(graph), usePruning(usePruning) {
}

int ExhaustiveSearch::findMinimumPath(int start, int target) {
    int cantNodes = graph.size();
    visited.assign(cantNodes, false);
    bestCost = INT_MAX;
    currentPath.clear();
    bestPath.clear();
    iterations = 0; 

    visited[start] = true;
    backtrack(start, target, 0);

    return bestCost;
}


void ExhaustiveSearch::backtrack(int current, int target, int accumulatedCost) {
    iterations++;

    currentPath.push_back(current);

    if (current == target) {
        if (accumulatedCost < bestCost) {
            bestCost = accumulatedCost;
            bestPath = currentPath;
        }
        currentPath.pop_back();
        return;
    }

    for (const auto& neighbor : graph.getNeighbors(current)) {
        int nextNode = neighbor.first;
        int edgeCost = neighbor.second;

        if (!visited[nextNode]) {
            if (usePruning) {
                if (accumulatedCost + edgeCost >= bestCost) {
                    continue;
                }
            }
            visited[nextNode] = true;
            backtrack(nextNode, target, accumulatedCost + edgeCost);
            visited[nextNode] = false;
        }
    }

    currentPath.pop_back();
}

std::vector<int> ExhaustiveSearch::getBestPath() const {
    return bestPath;
}

int ExhaustiveSearch::getIterationCount() const {
    return iterations;
}