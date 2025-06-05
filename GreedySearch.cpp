#include "GreedySearch.hpp"
#include <unordered_set>
#include <limits>

using namespace std;
using namespace std::chrono;

GreedySearch::GreedySearch(const unordered_map<int, vector<pair<int, int>>>& graph)
    : graph(graph) {}

std::vector<int> GreedySearch::findPath(int start, int target) {
    unordered_set<int> visited;
    vector<int> path;
    int current = start;
    iterations = 0;

    auto startTime = high_resolution_clock::now();

    while (current != target) {
        path.push_back(current);
        visited.insert(current);
        ++iterations;

        const auto& neighbors = graph[current];
        int minCost = numeric_limits<int>::max();
        int nextNode = -1;

        for (const auto& neighbor : neighbors) {
            int node = neighbor.first;
            int cost = neighbor.second;

            if (visited.find(node) == visited.end() && cost < minCost) {
                minCost = cost;
                nextNode = node;
            }
        }

        if (nextNode == -1) {
            durationMs = duration<double, std::milli>(high_resolution_clock::now() - startTime).count();
            return {}; // No se encontró ruta
        }

        current = nextNode;
    }

    path.push_back(target);

    auto endTime = high_resolution_clock::now();
    durationMs = duration<double, std::milli>(endTime - startTime).count();

    return path;
}

int GreedySearch::getIterationCount() const {
    return iterations;
}

double GreedySearch::getElapsedTimeMs() const {
    return durationMs;
}