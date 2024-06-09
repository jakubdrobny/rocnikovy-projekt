#ifndef Claus_H
#define Claus_H

#include "Literal.h"

#include <vector>

class Claus {
    public:
        std::vector<Literal> literals;

        Claus() {}

        void addLiteral(Literal literal);
        void print();
};

#endif