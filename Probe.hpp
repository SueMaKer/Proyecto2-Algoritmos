#ifndef PROBE_HPP
#define PROBE_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Probe {
public:
    
    Probe();

   
    void setGraph(const std::unordered_map<std::string, std::vector<std::string>>& universeGraph);

   
    std::vector<std::string> rapidSight(const std::string& fromNode);

  
    std::vector<std::string> deepProbe(const std::string& fromNode);

private:
    std::unordered_map<std::string, std::vector<std::string>> graph;

    void dfsHelper(const std::string& node, int depth, std::vector<std::string>& result);
};

#endif