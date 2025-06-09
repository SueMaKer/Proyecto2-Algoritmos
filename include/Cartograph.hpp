#ifndef CARTOGRAPH_HPP
#define CARTOGRAPH_HPP

#include <string>
#include <unordered_map>
#include <vector>

class Cartograph {
public:
    
    Cartograph();

    
    void setGraph(const std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& costGraph);

    
    int pathfinder(const std::string& start, const std::string& end);

    
    std::unordered_map<std::string, std::unordered_map<std::string, int>> starMapper();

private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
};

#endif