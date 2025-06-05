#ifndef BFS_HPP
#define BFS_HPP

#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <chrono>

class BFS {
public:
    BFS(const std::unordered_map<int, std::vector<int>>& graph);
    std::vector<int> getNeighbors(int startNode);
    std::vector<int> getNeighborsWithTimer(int startNode); // Nuevo método con tiempo
    int getIterationCount() const;                         // Obtener iteraciones
    double getElapsedTimeMs() const;                       // Obtener duración

private:
    std::unordered_map<int, std::vector<int>> graph;
    int iterations = 0;
    double elapsedTimeMs = 0.0;
};

#endif // BFS_HPP