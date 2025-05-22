#include "Player.hpp"
#include <iostream>

using namespace std;

Player::Player(const std::string& initialName) {
    name = initialName;
    etherium = 0; 
}

int Player::getEtherium() const {
    return etherium;
}

void Player::addEtherium(int amount) {
    if (amount > 0) {
        etherium += amount;
    } else {
        std::cout << "Invalid amount of Etherium to add." << std::endl;
    }
}

bool Player::spendEtherium(int amount) {
    if (amount > 0 && etherium >= amount) {
        etherium -= amount;
        return true;
    } else if (amount <= 0) {
        std::cout << "Invalid amount of Etherium to spend." << std::endl;
    } else {
        std::cout << "Not enough Etherium to use." << std::endl;
    }
    return false;
}

std::string Player::getName() const {
    return name;
}

void Player::displayStatus() const {
    cout << "Player: " << name << std::endl;
    cout << "Amount of Etherium: " << etherium << std::endl;
}

// This function will use a probe to explore from a planet
//Pending implementation
//void Player::useProbe(Probe* probe, Planet* from) {}

//This function will use the cartographer to calculate cost between two planets
//Pending implementation
//int Player::useCartographer(Cartographer* cartographer, Planet* origin, Planet* destination) {}

//This function will use a ship to attack the boss on a planet
//Pending implementation
//void Player::attackBoss(Planet* planet, Ship* usedShip) {}

// This function will add a ship to the player's fleet
//Pending implementation
//void Player::addShip(Ship* ship) {}

