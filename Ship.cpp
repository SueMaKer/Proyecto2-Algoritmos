#include "Ship.hpp"
#include "Config.hpp"

Ship::Ship() {
    baseDamage = Config::DEFAULT_SHIP_DAMAGE; 
}


double Ship::calculateEffectiveDamage(int iterations) const {
    if (iterations == 0) return 0.0; 
    return baseDamage / (iterations * iterations);
}
