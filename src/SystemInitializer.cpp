#include "SystemInitializer.hpp"
#include <random>
#include <chrono>

void SystemInitializer::generateMatrix(PlanetSystem& system, double removalProbability) {
    size_t n = system.getPlanetCount();
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, Config::INF));
    std::mt19937 rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> weightDist(1, 20);
    RandomBoolGenerator remover(removalProbability);

    // Conectar completamente con pesos
    for (size_t i = 0; i < n; ++i) {
        matrix[i][i] = 0;
        for (size_t j = i + 1; j < n; ++j) {
            int weight = weightDist(rng);
            matrix[i][j] = matrix[j][i] = weight;
        }
    }

    // Intentar eliminar conexiones al azar
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (matrix[i][j] != Config::INF && remover.get()) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i] = Config::INF;

                if (!isConnected(matrix)) {
                    matrix[i][j] = matrix[j][i] = temp; // restaurar
                }
            }
        }
    }

    system.setAdjacencyMatrix(matrix);
}

void SystemInitializer::ensureConnectivity(std::vector<std::vector<int>>& matrix) {
    // No se usa por ahora (reservado para lógica futura)
}

bool SystemInitializer::isConnected(const std::vector<std::vector<int>>& matrix) {
    size_t n = matrix.size();
    std::vector<bool> visited(n, false);
    dfs(0, matrix, visited);

    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

void SystemInitializer::dfs(int node, const std::vector<std::vector<int>>& matrix, std::vector<bool>& visited) {
    visited[node] = true;
    for (size_t i = 0; i < matrix[node].size(); ++i) {
        if (matrix[node][i] != Config::INF && !visited[i]) {
            dfs(i, matrix, visited);
        }
    }
}
