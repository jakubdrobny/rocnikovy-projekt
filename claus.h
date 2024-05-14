#ifndef claus_H
#define claus_H

#include "Literal.h"

#include <vector>

class clause {
    public:
        std::vector<Literal> literals;

        claus() {}

        void addLiteral(Literal literal);
        void print();
};

#endif