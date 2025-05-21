#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>

class Ship {
public:
   
    Ship();

   
    void setBaseDamage(double baseDamage);

   
    virtual int executeAttack() = 0;

   
    double calculateEffectiveDamage(int iterations) const;

protected:
    double baseDamage;
};

#endif