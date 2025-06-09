#pragma once
#include <random>

class RandomBoolGenerator {
private:
    std::mt19937 rng;
    std::bernoulli_distribution distribution;

public:
    // Constructor: probabilidad de que sea true (por defecto 50%)
    RandomBoolGenerator(double probability = 0.5);

    bool get();
};