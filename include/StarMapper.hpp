#ifndef STAR_MAPPER_HPP
#define STAR_MAPPER_HPP

#include "Ship.hpp"
#include "FloydWarshall.hpp"
#include "Config.hpp"
#include <vector>
#include <string>

using namespace std;

class StarMapper : public Ship {
private:
    const vector<vector<int>>* routeCostsMatrixPtr;
    const vector<int>* exploredPlanetsPtr;
    FloydWarshall floyd;

public:
    StarMapper(const vector<vector<int>>* adjacencyMatrix, const vector<int>* exploredPlanetsPtr);
    
    void update();
    
    void updateExploredPlanetsPtr(const vector<int>* newPtr);
    void updateRouteCostsMatrixPtr(const vector<vector<int>>* newMatrixPtr);

    vector<string> getEtheriumCostsReport() const;

    int getCost(int from, int to) const;
};

#endif
