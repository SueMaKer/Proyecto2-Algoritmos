#pragma once
#include <vector>
#include "PlanetSystem.hpp"

class Universe {
private:
    std::vector<PlanetSystem> systems;

public:
    void addSystem(const PlanetSystem& system);

    const std::vector<PlanetSystem>& getSystems() const;

    void printAll() const;

    int getSystemCount() const;

    PlanetSystem& getSystem(int index) ;
};