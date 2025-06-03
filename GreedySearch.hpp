#ifndef GREEDY_SEARCH_HPP
#define GREEDY_SEARCH_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class GreedySearch {
public:
    GreedySearch(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph);
    std::vector<int> findPath(int start, int target); // Returns a greedy path

private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
};

#endif // GREEDY_SEARCH_HPP
