#include "RandomBoolGenerator.hpp"
#include <chrono>

RandomBoolGenerator::RandomBoolGenerator(double probability)
    : rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())),
      distribution(probability) {}

bool RandomBoolGenerator::get() {
    return distribution(rng);
}