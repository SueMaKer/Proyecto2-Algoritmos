#include "PlanetSystem.hpp"

PlanetSystem::PlanetSystem(const std::string& name, const std::string& sector, const std::string& alliance) 
    : name(name), sector(sector), alliance(alliance) {}

void PlanetSystem::addPlanet(const Planet& planet) {
    planets.push_back(planet);
    // Resize adjacency matrix
    for (auto& row : adjacencyMatrix) {
        row.resize(planets.size(), 0);
    }
    adjacencyMatrix.resize(planets.size(), std::vector<int>(planets.size(), 0));
}

void PlanetSystem::addPlanet(const std::string& name, int health, bool hasResource) {
    addPlanet(Planet(name, health, hasResource));
}

Planet& PlanetSystem::getPlanet(int index) {
    if (index < 0 || index >= planets.size()) {
        throw std::out_of_range("Planet index out of range");
    }
    return planets[index];
}

const Planet& PlanetSystem::getPlanet(int index) const {
    if (index < 0 || index >= planets.size()) {
        throw std::out_of_range("Planet index out of range");
    }
    return planets[index];
}

void PlanetSystem::setConnection(int fromIndex, int toIndex, int weight) {
    if (fromIndex < 0 || fromIndex >= planets.size() || 
        toIndex < 0 || toIndex >= planets.size()) {
        throw std::out_of_range("Planet index out of range");
    }
    adjacencyMatrix[fromIndex][toIndex] = weight;
    adjacencyMatrix[toIndex][fromIndex] = weight; // Assuming undirected graph
}

void PlanetSystem::setAdjacencyMatrix(const std::vector<std::vector<int>>& matrix) {
    if (matrix.size() != planets.size() || (!matrix.empty() && matrix[0].size() != planets.size())) {
        throw std::invalid_argument("Matrix dimensions don't match planet count");
    }
    adjacencyMatrix = matrix;
}

int PlanetSystem::getConnectionWeight(int fromIndex, int toIndex) const {
    if (fromIndex < 0 || fromIndex >= planets.size() || 
        toIndex < 0 || toIndex >= planets.size()) {
        throw std::out_of_range("Planet index out of range");
    }
    return adjacencyMatrix[fromIndex][toIndex];
}

std::vector<bool> PlanetSystem::bfsFromPlanet(int startIndex) const {
    std::vector<bool> discovered(planets.size(), false);
    if (startIndex < 0 || startIndex >= planets.size()) return discovered;

    std::queue<int> q;
    q.push(startIndex);
    discovered[startIndex] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < planets.size(); ++v) {
            if (adjacencyMatrix[u][v] > 0 && !discovered[v]) {
                discovered[v] = true;
                q.push(v);
            }
        }
    }

    return discovered;
}

void PlanetSystem::dfsFromPlanet(int startIndex, std::function<void(int)> visitCallback) const {
    std::vector<bool> visited(planets.size(), false);
    std::function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        if (visitCallback) visitCallback(u);

        for (int v = 0; v < planets.size(); ++v) {
            if (adjacencyMatrix[u][v] > 0 && !visited[v]) {
                dfs(v);
            }
        }
    };

    if (startIndex >= 0 && startIndex < planets.size()) {
        dfs(startIndex);
    }
}

std::vector<int> PlanetSystem::dijkstra(int startIndex) const {
    std::vector<int> dist(planets.size(), Config::INF);
    if (startIndex < 0 || startIndex >= planets.size()) return dist;

    std::vector<bool> visited(planets.size(), false);
    dist[startIndex] = 0;

    for (int i = 0; i < planets.size(); ++i) {
        int u = -1;
        for (int j = 0; j < planets.size(); ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1 || dist[u] == Config::INF) break;
        visited[u] = true;

        for (int v = 0; v < planets.size(); ++v) {
            int weight = adjacencyMatrix[u][v];
            if (weight > 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

std::vector<std::vector<int>> PlanetSystem::floydWarshall() const {
    std::vector<std::vector<int>> dist = adjacencyMatrix;

    // Initialize diagonal and INF for unconnected nodes
    for (int i = 0; i < planets.size(); ++i) {
        for (int j = 0; j < planets.size(); ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (dist[i][j] == 0) {
                dist[i][j] = Config::INF;
            }
        }
    }

    for (int k = 0; k < planets.size(); ++k) {
        for (int i = 0; i < planets.size(); ++i) {
            for (int j = 0; j < planets.size(); ++j) {
                if (dist[i][k] != Config::INF && dist[k][j] != Config::INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}

void PlanetSystem::printAdjacencyMatrix() const {
    std::cout << "Adjacency Matrix for " << name << ":\n";
    for (const auto& row : adjacencyMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

void PlanetSystem::print() const {
    std::cout << "System: " << name << " (Sector: " << sector << ", Alliance: " << alliance << ")\n";
    std::cout << "Planets:\n";
    for (size_t i = 0; i < planets.size(); ++i) {
        std::cout << "  " << i << ": " << planets[i].getName() 
                  << " (Health: " << planets[i].getHealth() 
                  << ", Resources: " << (planets[i].hasResourceSite() ? "Yes" : "No")
                  << ", Visited: " << (planets[i].wasVisited() ? "Yes" : "No") << ")\n";
    }
    printAdjacencyMatrix();
}