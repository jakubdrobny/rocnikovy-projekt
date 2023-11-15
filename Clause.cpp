#include "Clause.h"
#include "Literal.h"

void Clause::add(Literal literal) {
    this->literals.push_back(literal);
}

void Clause::print() {
    for (int idx = 0; idx < (int)this->literals.size(); idx++) {
        if (idx) cout << " ";
        this->literals[idx].print();
    }
}