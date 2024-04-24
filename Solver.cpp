#include "Solver.h"

int Solver::nVars() {
    return (int)this->assigns.size();
}

int Solver::nAssigns() {
    return (int)this->trail.size();
}

int Solver::nConstraints() {
    return (int)this->constrs.size();
}

int Solver::nLearnts() {
    return (int)this->learnts.size();
}

lbool Solver::value(int x) {
    lbool elem;

    if (x >= 0 && x < this->nAssigns()) {
        elem = this->assigns[x];
    }

    return elem;
}

lbool Solver::value(lit p) {
    lbool elem;

    int idx = var(p);
    if (idx >= 0 && idx < this->assigns.size()) {
        elem = sign(p) ? -this->assigns[idx] : this->assigns[idx];
    }

    return elem;
}

int Solver::decisionLevel() {
    return (int)this->trail_lim.size();
}

int Solver::newVar() {
    int index = nVars();
    this->watches.push();
    this->watches.push();
    this->undos.push();
    this->reason.push();
    this->assigns.push(NOTHING);
    this->level.push(-1);
    this->activity.push(0);
    this->order.newVar();
    return index;
}