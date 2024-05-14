#include "claus.h"

#include <iostream>

void claus::addLiteral(Literal literal) {
    this->literals.push_back(literal);
}

void claus::print() {
    for (int idx = 0; idx < (int)this->literals.size(); idx++) {
        if (idx) std::cout << " v ";
        this->literals[idx].print();
    }
    std::cout << "\n";
}