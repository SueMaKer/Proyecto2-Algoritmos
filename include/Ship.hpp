#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>

class Ship {
public:
   
    Ship();
   
    

    double calculateEffectiveDamage(int iterations) const;

protected:
    int iterations;
    double baseDamage;
};

#endif