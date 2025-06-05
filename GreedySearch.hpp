#ifndef GREEDY_SEARCH_HPP
#define GREEDY_SEARCH_HPP

#include <unordered_map>
#include <vector>
#include <utility>
#include <chrono>

class GreedySearch {
public:
    GreedySearch(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph);

    std::vector<int> findPath(int start, int target); // Realiza la búsqueda greedy

    int getIterationCount() const;           // Retorna cuántas iteraciones se hicieron
    double getElapsedTimeMs() const;         // Retorna la duración de la búsqueda en milisegundos

private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
    int iterations = 0;
    double durationMs = 0.0;
};

#endif // GREEDY_SEARCH_HPP