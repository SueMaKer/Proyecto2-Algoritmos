#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

class Player {
private:
    std::string name;
    int etherium; 
    //std::vector<std::unique_ptr<Ship>> fleet; // Player's fleet of ships, pending implementation

public:
    Player(const std::string& initialName);

    // Game resources
    int getEtherium() const;
    void addEtherium(int amount);
    bool spendEtherium(int amount);

     //Player's information
    std::string getName() const;
    void displayStatus() const;

    // Actions pending implementation
    
    //int useCartographer(Cartographer* cartographer, Planet* origin, Planet* destination);
    //void attackBoss(Planet* planet, Ship* usedShip);
    //void addShip(Ship* ship);
    //void useProbe(Probe* probe, Planet* from)
};

#endif // PLAYER_HPP
