#include "Universe.hpp"
#include <iostream>

void Universe::printAll() const {
    for (const auto& system : systems) {
        system.print(); 
    }
}

void Universe::addSystem(const PlanetSystem& system) {
    systems.push_back(system);
}

const std::vector<PlanetSystem>& Universe::getSystems() const {
    return systems;
}


int Universe::getSystemCount() const {
    return systems.size();
}

PlanetSystem& Universe::getSystem(int index){
    return systems[index];
}