#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>

class Planet {
private:
    std::string name;
    std::string description;

    bool isVisited;

    std::vector<Planet*> neighbors; 
public:
    // Constructor
    Planet(const std::string& name, const std::string& description, bool combat, bool resources);

    // Destructor
    ~Planet();

    std::string getName() const;

    
    void addNeighbor(Planet* neighbor);

    std::vector<Planet*> getNeighbors() const;


    void markVisited();

    bool wasVisited() const;

    void printInfo() const;
};

#endif 
