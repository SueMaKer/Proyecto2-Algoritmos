#include "LocalSearch.hpp"

//Constructor of the LocalSearch class that initializes the neighbor generator and evaluation function.
LocalSearch::LocalSearch(NeighborGenerator generator, EvaluationFunction evaluator)
    : generateNeighbors(generator), evaluate(evaluator) {}

// Runs the local search algorithm starting from an initial solution.
LocalSearch::Solution LocalSearch::run(const Solution& initialSolution) {
    Solution current = initialSolution;
    double bestScore = evaluate(current);
    bool improved = true;

    while (improved) {
        improved = false;
        vector<Solution> neighbors = generateNeighbors(current);

        for (const auto& neighbor : neighbors) {
            double score = evaluate(neighbor);
            if (score < bestScore) { // Assuming lower score is better
                current = neighbor;
                bestScore = score;
                improved = true;
                break;
            }
        }
    }

    return current;
}
