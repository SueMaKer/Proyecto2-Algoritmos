#pragma once
#include "Universe.hpp"
#include "CSVReader.hpp"
#include "Interfaz.hpp"
#include "Player.hpp"

class GameManager {
private:
    Universe universe;
    Player player;
    Interfaz interfaz;

public:
    GameManager();
    bool loadUniverse(const std::string& filename);
    void run();
    Universe& getUniverse();  
};
