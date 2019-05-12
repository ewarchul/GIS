//
// Created by Konstantin on 21.04.2019.
//

#ifndef BAGENERATOR_RANDOM_H
#define BAGENERATOR_RANDOM_H

class Random {
public:
    virtual unsigned long getLong(unsigned long bound, unsigned long lower = 0) = 0;
};


#endif //BAGENERATOR_RANDOM_H
