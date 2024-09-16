//
// Created by Shoham on 15/09/2024.
//

#ifndef MONOPOLY_DICE_H
#define MONOPOLY_DICE_H
#include <random>
#include <utility>

class Dice {

    std::random_device rd;              // Obtain a random number from hardware
    std::mt19937 gen;                  // Seed the generator
    std::uniform_int_distribution<> dis; // Define the range
public:
    // Constructor: initializes random number generator
    Dice();
    // Get the result of roll dice
    std::pair<int, int> roll();

};


#endif //MONOPOLY_DICE_H
