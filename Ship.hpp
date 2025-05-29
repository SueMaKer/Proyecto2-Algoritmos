#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>

class Ship {
public:
   
    Ship();
   
    //virtual int executeAttack() = 0;

    double calculateEffectiveDamage(int iterations) const;

protected:
    int iterations;
    double baseDamage;
};

#endif