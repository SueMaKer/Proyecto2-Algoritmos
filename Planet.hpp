#ifndef PLANET_HPP
#define PLANET_HPP

#include <string>
#include <vector>

class Planet {
private:
    std::string name;
    std::string description;
    bool hasCombat;
    bool hasResources;
    bool isVisited;
    int health;

    std::vector<Planet*> neighbors;

public:
    Planet(const std::string& name, bool combat, bool resources);
    ~Planet();

    std::string getName() const;
    std::string getDescription() const;

    int getHealth() const;
    void takeDamage(int damage);
    bool hasCombatZone() const;
    bool hasResourceSite() const;

    void addNeighbor(Planet* neighbor);
    std::vector<Planet*> getNeighbors() const;

    void markVisited();
    bool wasVisited() const;

    int setHealth(int health) ;

    void print() const;
};

#endif // PLANET_HPP
