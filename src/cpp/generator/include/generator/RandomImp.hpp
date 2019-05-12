//
// Created by Konstantin on 21.04.2019.
//

#ifndef BAGENERATOR_RANDOMIMP_HPP
#define BAGENERATOR_RANDOMIMP_HPP

#include "Random.h"
#include <random>
class RandomImp : public Random {
private:
    std::default_random_engine generator;
public:
    // TODO probably slow try recr
    unsigned long getLong(unsigned long bound, unsigned long lower = 0) override {
        std::uniform_int_distribution<unsigned long> dist(lower, bound - 1);
        return dist(generator);
    }

    RandomImp() {

    }
};

#endif //BAGENERATOR_RANDOMIMP_HPP
