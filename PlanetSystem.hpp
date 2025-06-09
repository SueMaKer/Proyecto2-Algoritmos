#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <functional>

#include "Planet.hpp"
#include "Config.hpp"

class PlanetSystem {
private:
    std::string name;
    std::string sector;
    std::string alliance;
    std::vector<Planet> planets;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    PlanetSystem(const std::string& name, const std::string& sector = "", const std::string& alliance = "");

    // Planet management
    void addPlanet(const Planet& planet);
    void addPlanet(const std::string& name, int health, bool hasResource);
    Planet& getPlanet(int index);
    const Planet& getPlanet(int index) const;
    size_t getPlanetCount() const { return planets.size(); }
    
    // Connection management
    void setConnection(int fromIndex, int toIndex, int weight);
    void setAdjacencyMatrix(const std::vector<std::vector<int>>& matrix);
    int getConnectionWeight(int fromIndex, int toIndex) const;
    const std::vector<std::vector<int>>& getAdjacencyMatrix() const { return adjacencyMatrix; }
    
    // Algorithms
    std::vector<bool> bfsFromPlanet(int startIndex) const;
    void dfsFromPlanet(int startIndex, std::function<void(int)> visitCallback = nullptr) const;
    std::vector<int> dijkstra(int startIndex) const;
    std::vector<std::vector<int>> floydWarshall() const;
    
    // Utility
    std::string getName() const { return name; }
    std::string getSector() const { return sector; }
    std::string getAlliance() const { return alliance; }
    void printAdjacencyMatrix() const;
    void print() const;
};