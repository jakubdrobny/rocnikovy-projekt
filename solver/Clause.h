#ifndef Clause_H
#define Clause_H

#include "Vector.h"

class Clause : public Constr {
    public:
        bool learnt;
        float activity;
        Vector<lit> *lits;

        static bool Clause_new(Solver *S, Vector<lit> *ps, bool learnt, Clause *out_clause) {}
        bool locked(Solver *S);
        void remove(Solver *S);
        bool simplify(Solver *S);
        bool propagate(Solver *S, lit p);
        void calcReason(Solver *s, lit p, Vector<lit> *out_reason);
};

#endif