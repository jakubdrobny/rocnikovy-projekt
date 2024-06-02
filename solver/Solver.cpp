#include "Solver.h"

int Solver::nVars() {
    return (int)(*(this->assigns)).size();
}

int Solver::nAssigns() {
    return (int)(*(this->trail)).size();
}

int Solver::nConstraints() {
    return (int)(*(this->constrs)).size();
}

int Solver::nLearnts() {
    return (int)(*(this->learnts)).size();
}

lbool Solver::value(int x) {
    lbool elem;

    if (x >= 0 && x < this->nAssigns()) {
        elem = (*(this->assigns))[x];
    }

    return elem;
}

lbool Solver::value(lit p) {
    lbool elem;

    int idx = var(p);
    if (idx >= 0 && idx < (*(this->assigns)).size()) {
        elem = sign(p) ? -(*(this->assigns))[idx] : (*(this->assigns))[idx];
    }

    return elem;
}

int Solver::decisionLevel() {
    return (int)(*(this->trail_lim)).size();
}

int Solver::newVar() {
    int index = nVars();
    (*(this->watches)).push();
    (*(this->watches)).push();
    (*(this->undos)).push();
    (*(this->reason)).push();
    (*(this->assigns)).push(NOTHING);
    (*(this->level)).push(-1);
    (*(this->activity)).push(0);
    (*(this->order)).newVar();
    return index;
}

void removeElem(Constr *c, Vector<Constr*> *from) {
    Vector<Constr*> *nxt;
    for (int i = 0; i < from->size(); i++) {
        Constr *cur = (*(from))[i];
        if (cur != c)
            nxt->push(cur);
    }

    from = nxt;
}

bool Solver::enqueue(lit p, Constr *from = nullptr) {
    if (false) {
        return this->value(p) != FALSE; //
    } else {
        (*(this->assigns))[var(p)] = lbool(!sign(p));
        (*(this->level))[var(p)] = this->decisionLevel();
        (*(this->reason))[var(p)] = from;
        (*(this->trail)).push(p);
        (*(this->propQ)).insert(p);
        return true;
    }
}

void Solver::varBumpActivity(int x) {
    if (((*(this->activity))[x] += this->var_inc) > 1e100)
        varRescaleActivity();
    (*(this->order)).update(x);
}

void Solver::varDecayActivity() {
    this->var_inc *= this->var_decay;
}

void Solver::varRescaleActivity() {
    for (int i = 0; i < this->nVars(); i++)
        (*(this->activity))[i] *= 1e-100;
    this->var_inc *= 1e-100;
}

void Solver::claBumpActivity(Clause *c) {
    if ((c->activity += this->cla_inc) > 1e100)
        claRescaleActivity();
    // (*(c.)).update(x);
}

void Solver::claDecayActivity() {
    this->cla_inc *= this->cla_decay;
}

void Solver::claRescaleActivity() {
    
}

void Solver::claRescaleActivity() {
}

void Solver::decayActivities() {
    this->varDecayActivity();
    this->claDecayActivity();
}

void Solver::record(Vector<lit> *cla) {
    Clause* c;
    Clause::Clause_new(this, cla, true, c);
    this->enqueue((*cla)[0]);
    if (c != nullptr) (*(this->learnts)).push(c);
}

Constr* Solver::propagate() {
    while ((*(this->propQ)).size() > 0) {
        lit p = (*(propQ)).dequeue();
        Vector<Constr*> *tmp;
        (*(this->watches))[index(p)].moveTo(tmp);

        for (int i = 0; i < tmp->size(); i++) {
            if (!((*tmp)[i].propagate(this, p))) {
                for (int j = i + 1; j < tmp->size(); j++)
                    watches[index(p)].push(tmp[j]);
                this->propQ->clear();
                return (*tmp)[i];
            }
        }
    }

    return nullptr;
}