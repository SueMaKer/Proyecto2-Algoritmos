#include "GameManager.hpp"
#include <iostream>

bool GameManager::loadUniverse(const std::string& filename) {
    return CSVReader::loadUniverseFromCSV(filename, universe);
}

void GameManager::run() {
    //interfaz.run();            // Lanza el bucle de visualización/interacción
}

Universe& GameManager::getUniverse() {
    return universe;
}
