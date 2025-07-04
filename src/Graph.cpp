
#include "Graph.hpp"

Graph::Graph(int nodes) : cantNodes(nodes), adjacencyList(nodes) {}

void Graph::addEdge(int u, int v, int weight) {
    adjacencyList[u].push_back({v, weight});
    
}

const vector<pair<int, int>>& Graph::getNeighbors(int node) const {
    return adjacencyList[node];
}

int Graph::size() const {
    return cantNodes;
}
