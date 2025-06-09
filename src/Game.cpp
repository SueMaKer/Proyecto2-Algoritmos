#include "Game.hpp"
#include <iostream>

Game::Game() {
    turn = 1; 
}

void Game::start() {
    
    std::cout << "Game started!" << std::endl;
    std::cout << "Turn: " << turn << std::endl;
}

void Game::nextTurn() {
    
    std::cout << "Next turn!" << std::endl;
    turn++;
    std::cout << "Turn: " << turn << std::endl;
}

void Game::showStatus() {

    std::cout << "Current turn: " << turn << std::endl;
}

int Game::getTurn() const {
    return turn;
}
