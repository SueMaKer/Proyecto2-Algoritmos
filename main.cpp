#include <iostream>
#include <unordered_map>
#include <vector>

#include "RapidSight.hpp"
#include "PathFinder.hpp"
#include "LightAssault.hpp"

int main() {
    std::unordered_map<int, std::vector<std::pair<int,int>>> graph = {
        {0, {{1, 4}, {2, 1}}},
        {1, {{0, 4}, {3, 1}}},
        {2, {{0, 1}, {3, 5}}},
        {3, {{1, 1}, {2, 5}, {4, 3}}},
        {4, {{3, 3}}}
    };

    // RapidSight test
    RapidSight rapidSight(graph);
    auto neighbors = rapidSight.getNeighbors(0);
    std::cout << "RapidSight neighbors of node 0: ";
    for (auto n : neighbors) std::cout << n << " ";
    std::cout << "\n";

    // Pathfinder test
    Pathfinder pathfinder(graph);
    int shortestCost = pathfinder.findShortestPathCost(0, 4);
    std::cout << "Pathfinder shortest path cost from 0 to 4: " << shortestCost << "\n";

    // LightAssault test
    LightAssault lightAssault(graph);
    auto greedyPath = lightAssault.findGreedyAttackPath(0, 4);
    std::cout << "LightAssault greedy attack path from 0 to 4: ";
    for (auto node : greedyPath) std::cout << node << " ";
    std::cout << "\n";

    return 0;
}
// This code tests the functionality of RapidSight, Pathfinder, and LightAssault classes.
// It initializes a graph, retrieves neighbors using RapidSight, finds the shortest path cost using Pathfinder,
// and finds a greedy attack path using LightAssault. The results are printed to the console.