#ifndef Clause_H
#define Clause_H

#include "Vector.h"

class Clause : public Constr {
    public:
        bool learnt;
        float activity;
        Vector<lit> *lits;

        static bool Clause_new(Solver *S, Vector<lit> *ps, bool learnt, Clause *out_clause) {}
};

#endif