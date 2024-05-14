#include "Clause.h"
#include "Solver.h"
#include "lit.h"

bool Clause::Clause_new(Solver *S, Vector<lit> *ps, bool learnt, Clause *out_clause) {
    out_clause = nullptr;

    if (!learnt) {
        int psSize = ps->size();
        for (int psIdx = 0; psIdx < psSize; psIdx++) {
            if (S->value((*ps)[psIdx]) == TRUE) {
                return true;
            }
        }
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
            // c->lits[1] = ps[max_i];
            // c->lits[max_i] = ps[1];

            
        }
    }
}