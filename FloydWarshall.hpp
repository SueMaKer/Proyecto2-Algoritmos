#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include "Config.hpp"
#include <vector>

using namespace std;

class FloydWarshall {
private:
    int cantNodes;
    vector<vector<int>> dist;
    vector<vector<int>> next;

public:
    FloydWarshall(int vertices);
    void addEdge(int node1, int node2, int cost);
    void run();
    int getDistance(int node1, int node2) const;
    vector<int> getPath(int node1, int node2) const;
    void printDistanceMatrix() const;
};

#endif
