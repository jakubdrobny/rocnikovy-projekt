#include "Clause.h"

#include <iostream>

void Clause::addLiteral(Literal literal) {
    this->literals.push_back(literal);
}

void Clause::print() {
    for (int idx = 0; idx < (int)this->literals.size(); idx++) {
        if (idx) std::cout << " ";
        this->literals[idx].print();
    }
    std::cout << "\n";
}