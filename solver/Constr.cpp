#include "Constr.h"

// defaults to return false
bool Constr::simplify(Solver* S) {
    return false;
}

// default to do nothing
void Constr::undo(Solver* S, lit p) {}