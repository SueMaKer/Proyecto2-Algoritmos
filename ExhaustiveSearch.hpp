#ifndef EXHAUSTIVESEARCH_HPP
#define EXHAUSTIVESEARCH_HPP

#include "Ship.hpp"
#include "Graph.hpp"
#include <vector>
#include <climits>

using namespace std;

class ExhaustiveSearch : public Ship {
private:
    const Graph& graph;
    std::vector<bool> visited;
    int bestCost;
    std::vector<int> currentPath;
    std::vector<int> bestPath;
    bool usePruning = false;  


    void backtrack(int current, int target, int accumulatedCost);

public:
    ExhaustiveSearch(const Graph& graph, bool usePruning);

    int findMinimumPath(int start, int target);

    std::vector<int> getBestPath() const;

    int getIterationCount() const;
};
#endif 
