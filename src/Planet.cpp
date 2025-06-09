#include "Planet.hpp"
#include <iostream>

Planet::Planet(const std::string& name, bool combat, bool resources)
    : name(name), hasCombat(combat), hasResources(resources), isVisited(false) {}

Planet::~Planet() {

}

std::string Planet::getName() const {
    return name;
}

std::string Planet::getDescription() const {
    return description;
}


int Planet::getHealth() const{
    return health;
}

void Planet::takeDamage(int damage){
    health -= damage;
}

int Planet::setHealth(int health) {
    this->health = health;
}


bool Planet::hasCombatZone() const {
    return hasCombat;
}

bool Planet::hasResourceSite() const {
    return hasResources;
}

// Vecindad
void Planet::addNeighbor(Planet* neighbor) {
    neighbors.push_back(neighbor);
}

std::vector<Planet*> Planet::getNeighbors() const {
    return neighbors;
}

// Visita
void Planet::markVisited() {
    isVisited = true;
}

bool Planet::wasVisited() const {
return isVisited;
}

// Información
void Planet::print () const {
    std::cout << "Planeta: " << name << "\n";
    std::cout << "Zona de combate: " << (hasCombat ? "Sí" : "No") << "\n";
    std::cout << "Recursos disponibles: " << (hasResources ? "Sí" : "No") << "\n";
    std::cout << "Visitado: " << (isVisited ? "Sí" : "No") << "\n";
    std::cout << "Vecinos() : ";
    for (const auto& neighbor : neighbors) {
        std::cout << neighbor->getName() << " ";
    }
    std::cout << "\n";
}

