#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include <vector>
#include <functional>

using namespace std;

class LocalSearch {
public:
    using Solution = vector<int>;
    using NeighborGenerator = function<vector<Solution>(const Solution&)>;
    using EvaluationFunction = function<double(const Solution&)>;

    // Constructor that defines the neighbor generator and evaluation function
    LocalSearch(NeighborGenerator generator, EvaluationFunction evaluator);

    // executes the local search algorithm starting from an initial solution
    Solution run(const Solution& initialSolution);

private:
    NeighborGenerator generateNeighbors;
    EvaluationFunction evaluate;
};

#endif // LOCAL_SEARCH_HPP
