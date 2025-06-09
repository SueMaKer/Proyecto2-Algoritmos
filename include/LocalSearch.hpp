#ifndef LOCALSEARCH_HPP
#define LOCALSEARCH_HPP

#include <vector>
#include <chrono>

class LocalSearch {
private:
    const std::vector<std::vector<int>>& costMatrix;
    int node;
    int INF;
    std::vector<int> neighbors;
    int iterations;
    double duration;

public:
    // Constructor: take the adjacency matrix, the node to analyze, and the value of INF
    LocalSearch(const std::vector<std::vector<int>>& matrix, int startNode, int infinityValue = 1e9);

    // Excecutes the "local search"
    void run();

    // Return the neighbors found
    const std::vector<int>& getNeighbors() const;

    int getIterationCount() const;

    double getDuration () const;

    void runWithTiming();
};

#endif

