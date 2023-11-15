#include "CNF.h"
#include "Clause.h"

void CNF::loadFromGraph(Graph g) {
    // TODO
}

void CNF::print() {
    for (Clause clause : this->clauses) {
        clause.print();
    }
}