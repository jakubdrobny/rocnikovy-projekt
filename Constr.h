#ifndef Constr_H
#define Constr_H

#include "Solver.h"
#include "lit.h"

class Constr {
	public:
        virtual void remove(Solver* S); // must be defined
        virtual bool propagate(Solver* S, lit p); // must be defined
        virtual bool simplify(Solver* S); // defaults to return false;
        virtual void undo(Solver* S, lit p); // default to do nothing;
        virtual void calcReason(Solver* S, lit p, Vector<lit> *out_reason); // must be defined
};

#endif