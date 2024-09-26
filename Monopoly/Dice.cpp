
#include "Dice.hpp"
#include <ctime>

// Constructor: Seeds the random number generator
Dice::Dice()    : gen(rd()), dis(1, 6) {}// Dice range is from 1 to 6

std::pair<int, int> Dice::roll() {

    int roll1 = dis(gen); // Roll first dice
    int roll2 = dis(gen); // Roll second dice
    return std::make_pair(roll1, roll2);
}

