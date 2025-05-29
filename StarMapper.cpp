#include "StarMapper.hpp"
#include "Config.hpp"

StarMapper::StarMapper(const vector<vector<int>>* adjacencyMatrix, const vector<int>* exploredPlanetsPtr)
        : Ship(), exploredPlanetsPtr(exploredPlanetsPtr), floyd(adjacencyMatrix->size()) {
    // Agrega aristas desde la matriz de adyacencia
    for (int i = 0; i < adjacencyMatrix->size(); ++i) {
        for (int j = 0; j < (*adjacencyMatrix)[i].size(); ++j) {
            int cost = (*adjacencyMatrix)[i][j];
            if (cost < Config::INF / 2) {
                floyd.addEdge(i, j, cost);
            }
        }
    }
    floyd.run(); // Ejecuta algoritmo al construir
}

vector<string> StarMapper::getEtheriumCostsReport() const {
    vector<string> report;

    const vector<vector<int>>& matrix = *routeCostsMatrixPtr;
    const vector<int>& explored = *exploredPlanetsPtr;

    for (size_t i = 0; i < explored.size(); ++i) {
        for (size_t j = 0; j < explored.size(); ++j) {
            int from = explored[i];
            int to = explored[j];

            if (from != to) {
                int cost = matrix[from][to];

                if (cost != Config::INF) {
                    report.push_back("Route " + to_string(from) + " -> " + to_string(to) +
                                        ": " + to_string(cost) + " Ȅ");
                } else {
                    report.push_back("Route " + to_string(from) + " -> " + to_string(to) +
                                        ": Unknown");
                }
            }
        }
    }

    return report;
}



void StarMapper::update() {
    floyd = FloydWarshall(routeCostsMatrixPtr->size());  
    for (int i = 0; i < routeCostsMatrixPtr->size(); ++i) {
        for (int j = 0; j < routeCostsMatrixPtr->at(i).size(); ++j) {
            int cost = routeCostsMatrixPtr->at(i)[j];
            if (cost < Config::INF) {
                floyd.addEdge(i, j, cost);
            }
        }
    }
    floyd.run(); 
}


void StarMapper::updateExploredPlanetsPtr(const vector<int>* newPtr) {
    exploredPlanetsPtr = newPtr;
}

void StarMapper::updateRouteCostsMatrixPtr(const vector<vector<int>>* newMatrixPtr) {
    routeCostsMatrixPtr = newMatrixPtr;
    update();
}

//Para Pruebas
int StarMapper::getCost(int from, int to) const {
    return floyd.getDistance(from, to);
}
