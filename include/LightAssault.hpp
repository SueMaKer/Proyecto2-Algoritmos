#ifndef LIGHTASSAULT_HPP
#define LIGHTASSAULT_HPP

#include <unordered_map>
#include <vector>
#include <utility>

class LightAssault {
public:
    LightAssault(const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph);
    std::vector<int> findGreedyAttackPath(int startNode, int endNode);

private:
    const std::unordered_map<int, std::vector<std::pair<int,int>>>& graph_;
};

#endif
