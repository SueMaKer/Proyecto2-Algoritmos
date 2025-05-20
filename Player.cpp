#include "Player.hpp"

using namespace std;

Player::Player(const std::string& initialName) {
    name = initialName;
    etherium = 0; 
}

int Player::getEtherium() const {
    // Se obtiene la cantidad de etherium del jugador
    return 0;
}

void Player::addEtherium(int amount) {
    // Agrega etherium al jugador
}

bool Player::spendEtherium(int amount) {
    // Gasta etherium del jugador
    return false;
}

std::string Player::getName() const {
    // Retornará el nombre del jugador
    return "";
}

void Player::displayStatus() const {
    // muestra el estado del jugador
}
