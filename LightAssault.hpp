#ifndef LIGHTASSAULT_HPP
#define LIGHTASSAULT_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class LightAssault {
public:
    LightAssault(const std::unordered_map<int, std::vector<std::pair<int, int>>>& graph);
    std::vector<int> findGreedyAttackPath(int start, int goal);
    //int findGreedyAttackPath(int startNode, int endNode, std::vector<int>& path);

private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
};

#endif // LIGHTASSAULT_HPP
