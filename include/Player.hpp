#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

class Player {
private:
    std::string name;
    int etherium; 
    

public:
    Player(const std::string& initialName);

    
    int getEtherium() const;
    void addEtherium(int amount);
    bool spendEtherium(int amount);

    
    std::string getName() const;
    void displayStatus() const;

};

#endif // PLAYER_HPP
