//
// Created by Jesus Flores on 11.05.24.
//

#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>

class RandomDoubleGenerator {

    std::mt19937 gen;  // Mersenne Twister engine
    std::uniform_real_distribution<> distr;  // Uniform real distribution

public:
    // Constructor to initialize the generator and distribution
    RandomDoubleGenerator(double lower_bound, double upper_bound)
        : gen(std::random_device{}()), distr(lower_bound, upper_bound) {}

    // Method to generate a random double
    double getRandomDouble() {
        return distr(gen);
    }

    int getRandomInt() {
        return (int) distr(gen);
    }
};



#endif //RANDOMNUMBERGENERATOR_H
