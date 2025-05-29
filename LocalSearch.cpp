#include "LocalSearch.hpp"

// Constructor for the LocalSearch class
LocalSearch::LocalSearch(const std::vector<std::vector<int>>& matrix, int startNode, int infinityValue)
    : costMatrix(matrix), node(startNode), INF(infinityValue) {}

//Method to execute the local search algorithm
void LocalSearch::run() {
    neighbors.clear();
    iterations = 0;
    int size = costMatrix.size();
    for (int j = 0; j < size; ++j) {
        ++iterations;
        if (j != node && costMatrix[node][j] < INF) {
            neighbors.push_back(j);
        }
    }
}

// Method to return the neighbors found during the local search
const std::vector<int>& LocalSearch::getNeighbors() const {
    return neighbors;
}

