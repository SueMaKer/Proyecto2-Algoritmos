#ifndef GAME_HPP
#define GAME_HPP

class Game {
private:
    int turn;
    
public:
    Game(); 
    void start(); 
    void nextTurn();
    void showStatus();
    int getTurn() const;
};

#endif 