#include "GameManager.hpp"
#include <iostream>

bool GameManager::loadUniverse(const std::string& filename) {
    return CSVReader::loadUniverseFromCSV(filename, universe);
}

void GameManager::run() {
    //interfaz.run();            
}
Universe& GameManager::getUniverse() {
    return universe;
}
