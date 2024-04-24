#ifndef Solver_H
#define Solver_H

#include "Solver.h"
#include "Vector.h"
#include "lit.h"
#include "Queue.h"
#include "Vector.h"
#include "lbool.h"
#include "Constr.h"
#include "VarOrder.h"

class Solver {
	private:
        // Constraint database
        Vector<Constr> constrs; // List of problem onstraints.
        Vector<Clause> learnts; // List of learnt lauses.
        double cla_inc; // Clause ativity increment - amount to bump with.
        double cla_decay; // Decay fator for clause activity

        // Variable order
        Vector<double> activity; // Heuristic measurement of the activity of a variable.
        double var_inc; // Variable activity increment - amount to bump with.
        double var_decay; // Decay factor for variable ativity.
        VarOrder order; // Keeps track of the dynamic variable order.

        // Propagation
        Vector<Vector<Constr>> watches; // For each literal 'p', a list of constraints watching 'p'.
                                        // A constraint will be inspected when 'p' becomes true.
        Vector<Vector<Constr>> undos; // For each variable 'x', a list of constraints that need to
                                      // update when 'x' becomes unbound by backtraking.
        Queue<lit> propQ; // Propagation queue.

        // Assignments
        Vector<lbool> assigns; // The current assignments indexed on variables.
        Vector<lit> trail; // List of assignments in chronologial order.
        Vector<int> trail_lim; // { Separator indices for different decision levels in 'trail'
        Vector<Constr> reason; // For each variable, the constraint that implied its value
        Vector<int> level; // For each variable, the decision level it was assigned.
        int root_level; // Separates incremental and search assumptions.

    public:
        int nVars();
        int nAssigns();
        int nConstraints();
        int nLearnts();
        lbool value(int x);
        lbool value(lit p);
        int decisionLevel();
        int newVar();
};

#endif