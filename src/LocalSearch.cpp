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

// Method to get the number of iterations performed
int LocalSearch::getIterationCount() const {
    return iterations;
}

// Method to get the duration of the local search
double LocalSearch::getDuration() const {
    return duration;
}

// Method to run the local search with timing
void LocalSearch::runWithTiming() {
    auto start = std::chrono::high_resolution_clock::now(); // Start timing
    run();
    auto end = std::chrono::high_resolution_clock::now(); // End timing
    duration = std::chrono::duration<double, std::milli>(end - start).count(); 
}

