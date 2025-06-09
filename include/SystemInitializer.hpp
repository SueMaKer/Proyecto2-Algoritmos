#pragma once
#include "PlanetSystem.hpp"
#include "RandomBoolGenerator.hpp"
#include "Config.hpp"
#include <vector>
#include <random>

class SystemInitializer {
public:
    static void generateMatrix(PlanetSystem& system, double removalProbability);
private:
    static void ensureConnectivity(std::vector<std::vector<int>>& matrix);
    static bool isConnected(const std::vector<std::vector<int>>& matrix);
    static void dfs(int node, const std::vector<std::vector<int>>& matrix, std::vector<bool>& visited);
};
