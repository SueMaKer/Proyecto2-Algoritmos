#include "Game.hpp"
#include <iostream>

Game::Game() {
    turn = 1; //Es un 1 porque es el primer turno
}

void Game::start() {
//Inicialización del juego
}

void Game::nextTurn() {
// Lógica para avanzar al siguiente turno
}

void Game::showStatus() {
// Mostrar el estado actual del juego
}

int Game::getTurn() const {
    return turn;
}
