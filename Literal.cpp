#include "Literal.h"

#include <iostream>

void Literal::print() {
    std::cout << this->value;
}

int Literal::valueFromNodeAndColor(int K, bool negate) {
    return (negate ? -1 : 1) * ((this->node * K) + this->color);
}