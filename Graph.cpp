// Graph.cpp
#include "Graph.hpp"

Graph::Graph(const AdjacencyList& adj) : adjacencyList(adj) {}

// Returns a constant reference to the adjacency list of the graph.
const Graph::AdjacencyList& Graph::getAdjacencyList() const {
    return adjacencyList;
}
