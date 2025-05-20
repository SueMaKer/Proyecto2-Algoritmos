#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <memory>

class Player {
private:
    std::string name; // Player's name
    int etherium; // Amount of etherium per player
    //std::vector<std::unique_ptr<Ship>> fleet; // Player's fleet of ships

public:
    Player(const std::string& initialName);

    // Resources
    int getEtherium() const;
    void addEtherium(int amount);
    bool spendEtherium(int amount);

    // Actions
    //Pendientes de implementar


    // Info
    std::string getName() const;
    void displayStatus() const;
};

#endif // PLAYER_HPP
