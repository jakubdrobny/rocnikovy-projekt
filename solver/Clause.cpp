#include "Clause.h"
#include "Solver.h"
#include "lit.h"
#include <set>

bool Clause::Clause_new(Solver *S, Vector<lit> *ps, bool learnt, Clause *out_clause) {
    out_clause = nullptr;

    if (!learnt) {
        int psSize = ps->size();
        std::set<lit> seen;
        Vector<lit> *new_ps;

        for (int psIdx = 0; psIdx < psSize; psIdx++) {
            lit cur_lit = (*ps)[psIdx];
            if (S->value(cur_lit) == TRUE || seen.count(-cur_lit)) // if any literal in ps is true or both p and -p occur in ps, return true
                return true;

            if (S->value(cur_lit) != FALSE && !seen.count(cur_lit)) // only take non duplicates and not false literals
                new_ps->push(lit(cur_lit));

            seen.insert(cur_lit);
        }

        ps = new_ps;
    }

    if (ps->size() == 0) {
        return false;
    } else if (ps->size() == 1) {
        return S->enqueue((*ps)[0]);     // unit facts are enqueued
    } else {
        Clause* c = new Clause();
        ps->moveTo(c->lits);
        c->learnt = learnt;
        c->activity = 0;
        
        if (learnt) {
            int max_i = 0; // TODO: index of literal with highest decision level"
            c->lits[1] = ps[max_i];
            c->lits[max_i] = ps[1];

            S->claBumpActivity(c);
            for (int i = 0; i < ps->size(); i++)
                S->varBumpActivity((*ps)[i].getVal());
        }

        (*(S->watches))[index(-((*(c->lits))[0]))].push(c);
        (*(S->watches))[index(-((*(c->lits))[1]))].push(c);
        out_clause = c;

        return true;
    }
}

bool Clause::locked(Solver *S) {
    return (*(S->reason))[var((*(this->lits))[0])];
}

void Clause::remove(Solver *S) {
    S->removeElem(this, &((*(S->watches))[index(-((*(this->lits))[0]))]));
    S->removeElem(this, &((*(S->watches))[index(-((*(this->lits))[1]))]));
    delete this;
}

bool Clause::simplify(Solver *S) {
    int j = 0;
    for (int i = 0; i < (*(this->lits)).size(); i++) {
        lbool val = S->value((*(this->lits))[i]);
        if (val == TRUE) return true;
        else if (val == NOTHING) (*(this->lits))[j++] = (*(this->lits))[i];
    }
    this->lits->shrink(this->lits->size());
    return false;
}

bool Clause::propagate(Solver *S, lit p) {
    if ((*(this->lits))[0] == -p) {
        (*(this->lits))[0] = (*(this->lits))[1];
        (*(this->lits))[1] = -p;
    }

    if (S->value((*(this->lits))[0]) == TRUE) {
        (*(S->watches))[index(p)].push(this);
        return true;
    }

    for (int i = 2; i < this->lits->size(); i++) {
        if (S->value((*(this->lits))[i]) != FALSE) {
            (*(this->lits))[1] = (*(this->lits))[i];
            (*(this->lits))[i] = -p;
            (*(S->watches))[index(-((*(this->lits))[1]))].push(this); // insert clause into watcher list
            return true;
        }
    }

    (*(S->watches))[index(p)].push(this);
    return S->enqueue((*(this->lits))[0], this);
}

void Clause::calcReason(Solver *S, lit p, Vector<lit> *out_reason) {
    for (int i = ((p == NOTHING) ? 0 : 1); i < this->lits->size(); i++)
        out_reason->push(-((*(this->lits))[i]));
    if (this->learnt) S->claBumpActivity(this);
}