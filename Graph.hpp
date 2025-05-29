#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>

using namespace std;

class Graph {
private:
    int cantNodes;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Graph(int nodes);
    void addEdge(int u, int v, int weight);
    const vector<pair<int, int>>& getNeighbors(int node) const;
    int size() const;
};

#endif 
