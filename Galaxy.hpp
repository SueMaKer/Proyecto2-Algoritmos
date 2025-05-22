#ifndef GALAXY_HPP
#define GALAXY_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "Planet.hpp"

class Galaxy {
private:
    std::string name;
    std::string entryPlanetName;
    std::string exitPlanetName;
    std::unordered_map<std::string, Planet*> planets; // Map of planet names to Planet objects
    float linkProbability;

public:
    // Constructor
    Galaxy(const std::string& name, const std::string& entry, const std::string& exit, float linkProb);

    // Destructor
    ~Galaxy();

    void addPlanet(const std::string& planetName);

    void generateInternalLinks();

    // Ensures the subgraph is fully connected
    void ensureConnectivity();

    Planet* getEntryPlanet() const;

    Planet* getExitPlanet() const;

    std::vector<std::string> getPlanetNames() const;

    Planet* getPlanet(const std::string& planetName) const;

    void connectToNextGalaxy(Galaxy* nextGalaxy);


    void printGalaxyInfo() const;
};

#endif // GALAXY_H