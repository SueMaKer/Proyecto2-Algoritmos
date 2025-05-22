#include "Game.hpp"
#include <iostream>

Game::Game() {
    turn = 1; //It's the first turn
}

void Game::start() {
    //Game initialization logic
    std::cout << "Game started!" << std::endl;
    std::cout << "Turn: " << turn << std::endl;
}

void Game::nextTurn() {
    // Logic for the next turn
    std::cout << "Next turn!" << std::endl;
    turn++;
    std::cout << "Turn: " << turn << std::endl;
}

void Game::showStatus() {
// Show the status of the game
    std::cout << "Current turn: " << turn << std::endl;
}

int Game::getTurn() const {
    return turn;
}
