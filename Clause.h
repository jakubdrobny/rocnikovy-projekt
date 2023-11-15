#ifndef Clause_H
#define Clause_H

#include "Literal.h"

#include <vector>

class Clause {
    public:
        std::vector<Literal> literals;

        Clause() {}

        void add(Literal literal) {}
        void print() {}
};

#endif