// Graph.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <string>

class Graph {
public:
    // Type for the adjacency list representation of the graph
    using AdjacencyList = std::unordered_map<std::string, std::vector<std::string>>;
    Graph(const AdjacencyList& adj);
    const AdjacencyList& getAdjacencyList() const;

private:
    AdjacencyList adjacencyList;
};

#endif

