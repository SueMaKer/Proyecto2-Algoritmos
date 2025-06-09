#include "CSVReader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Planet.hpp"
#include "PlanetSystem.hpp"
#include "RandomBoolGenerator.hpp"
#include "SystemInitializer.hpp"

bool CSVReader::loadUniverseFromCSV(const std::string& filename, Universe& universe) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << "\n";
        return false;
    }

    std::string line;

    // Leer header y descartarlo
    if (!std::getline(file, line)) return false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            // Trim espacios
            token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), token.end());

            tokens.push_back(token);
        }

        if (tokens.size() < 3) continue;

        PlanetSystem system(tokens[0], tokens[1], tokens[2]);
        RandomBoolGenerator rng(0.3);  // 30% probabilidad de combate

        for (size_t i = 3; i < tokens.size() && i < 23; ++i) {
            if (!tokens[i].empty()) {
                bool hayCombate = rng.get();
                system.addPlanet(Planet(tokens[i], hayCombate, hayCombate));
            }
        }

        // Generar matriz de adyacencia con pesos y eliminar conexiones al azar sin romper la conectividad
        SystemInitializer::generateMatrix(system, 0.3);  // 30% de probabilidad de eliminar una conexión

        universe.addSystem(system);
    }

    return true;
}