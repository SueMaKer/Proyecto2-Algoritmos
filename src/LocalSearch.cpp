#include "LocalSearch.hpp"


LocalSearch::LocalSearch(const std::vector<std::vector<int>>& matrix, int startNode, int infinityValue)
    : costMatrix(matrix), node(startNode), INF(infinityValue) {}


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


const std::vector<int>& LocalSearch::getNeighbors() const {
    return neighbors;
}


int LocalSearch::getIterationCount() const {
    return iterations;
}


double LocalSearch::getDuration() const {
    return duration;
}


void LocalSearch::runWithTiming() {
    auto start = std::chrono::high_resolution_clock::now(); // Start timing
    run();
    auto end = std::chrono::high_resolution_clock::now(); // End timing
    duration = std::chrono::duration<double, std::milli>(end - start).count(); 
}

