#ifndef VarOrder_H
#define VarOrder_H

#include "Vector.h"
#include "lbool.h"

class VarOrder {
	public:
        VarOrder(Vector<lbool>* ref_to_assigns, Vector<double>* ref_to_activity);

        void newVar(); // Called when a new variable is created
        void update(int x); // Called when variable has increased in activity.
        void updateAll(); // Called when all variables have been assigned new activities.
        void undo(int x); // Called when variable is unbound (may be selected again).
        int select(); // Called to select a new, unassigned variable.
};

#endif