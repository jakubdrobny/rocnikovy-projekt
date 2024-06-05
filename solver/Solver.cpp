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
    if ((c->activity += this->cla_inc) > 1e100) // todo: neviem ci uplne takto to ma byt podla paperu
        claRescaleActivity();
}

void Solver::claDecayActivity() {
    this->cla_inc *= this->cla_decay;
}

void Solver::claRescaleActivity() {
    // todo neviem ako presne to urobit podla paperu zatial    
}

void Solver::decayActivities() {
    this->varDecayActivity();
    this->claDecayActivity();
}

void Solver::record(Vector<lit> *cla) {
    Clause* c; // will be set to created clause, or NULL if 'clause[]' is unit
    Clause::Clause_new(this, cla, true, c); // cannot fail at this point
    this->enqueue((*cla)[0]); // cannot fail at this point
    if (c != nullptr) (*(this->learnts)).push(c);
}

Constr* Solver::propagate() {
    while ((*(this->propQ)).size() > 0) {
        lit p = (*(propQ)).dequeue();
        Vector<Constr*> *tmp;
        (*(this->watches))[index(p)].moveTo(tmp);

        for (int i = 0; i < tmp->size(); i++) {
            Constr *cur = (*tmp)[i];
            if (!((*cur).propagate(this, p))) {
                for (int j = i + 1; j < tmp->size(); j++)
                    watches[index(p)].push(tmp[j]);
                this->propQ->clear();
                return cur;
            }
        }
    }

    return nullptr;
}

void Solver::reduceDB() {
    int i, j;
    double lim = this->cla_inc / this->nLearnts();

    //sortOnActivity(learnts); todo - 
    for (i = j = 0; i < this->nLearnts() / 2; i++) {
        if (!(*(this->learnts))[i]->locked(this))
            (*(this->learnts))[i]->remove(this);
        else
            (*(this->learnts))[j++] = (*(this->learnts))[i];
    }
    for (; i < this->nLearnts(); i++) {
        if (!(*(this->learnts))[i]->locked(this) && (*(this->learnts))[i]->activity < lim)
            (*(this->learnts))[i]->remove(this);
        else
            (*(this->learnts))[j++] = (*(this->learnts))[i];
    }

    this->learnts->shrink(i-j);
}

void Solver::analyze(Constr *confl, Vector<lit> *out_learnt, int *out_btlevel) {
    Vector<bool> *seen = new Vector<bool>(this->nVars(), FALSE);
    int counter = 0;
    lit p = EMPTY;
    Vector<lit> *p_reason = new Vector<lit>();

    out_learnt->push(); // leave room for the asserting literal
    out_btlevel = 0;

    do {
        p_reason->clear();
        confl->calcReason(this, p, p_reason); // invariant here: confl != NULL

        // trace reason for p
        for (int j = 0; j < p_reason->size(); j++) {
            lit q = (*p_reason)[j];
            if (!((*seen)[var(q)])) {
                (*seen)[var(q)] = true;
                if ((*level)[var(q)] == decisionLevel()) {
                    counter++;
                } else if ((*level)[var(q)] > 0) { // exclude variables from decision level 0
                    out_learnt->push(-q);
                    *out_btlevel = std::max(*out_btlevel, (*level)[var(q)]);
                }
            }
        }

        // select next literal to look at
        do {
            p = trail->last();
            confl = (*reason)[var(p)];
            undoOne();
        } while (!((*seen)[var(p)]));
        counter--;
    } while (counter > 0);
    (*out_learnt)[0] = -p;
}

Vector<Constr*>* cast_clause_to_constr(Vector<Clause*> *to_cast) {
    
}

bool Solver::simplifyDB() {
    if (this->propagate() != nullptr)
        return false;
    
    for (int type = 0; type < 2; type++) {
        Vector<Constr*> *cs = type ? cast_clause_to_constr(this->learnts) : this->constrs;
        int j = 0;
        
        for (int i = 0; i < cs->size(); i++) {
            if ((*cs)[i]->simplify(this))
                (*cs)[i]->remove(this);
            else
                (*cs)[j++] = (*cs)[i];
        }

        cs->shrink(cs->size() - j);
    }

    return true;
}

void Solver::undoOne() {
    lit p = trail->last();
    int x = var(p);
    (*(this->assigns))[x] = NOTHING;
    (*(this->reason))[x] = nullptr;
    (*(this->level))[x] = -1;
    this->order->undo(x);
    this->trail->pop();
    while ((*undos)[x].size() > 0) {
        (*undos)[x].last()->undo(this, p);
        (*undos)[x].pop();
    }
}

bool Solver::assume(lit p) {
    this->trail_lim->push(this->trail->size());
    return this->enqueue(p);
}

void Solver::cancel() {
    int c = this->trail->size() - this->trail_lim->last();
    for (; c != 0; c--)
        this->undoOne();
    this->trail_lim->pop();
}

void Solver::cancelUntil(int level) {
    while (this->decisionLevel() > level)
        this->cancel();
}

bool Solver::solve(Vector<lit> *assumps) {
    SearchParams *params = new SearchParams(0.95, 0.999);
    double no_of_conflicts = 100;
    double no_of_learnts = this->nConstraints() / 3;
    lbool status = NOTHING;

    for (int i = 0; i < assumps->size(); i++) {
        if (!assume((*assumps)[i]) || propagate != nullptr) {
            this->cancelUntil(0);
            return false;
        }
    }

    this->root_level = this->decisionLevel();

    while (status == NOTHING) {
        status = search((int)no_of_conflicts, (int)no_of_learnts, params);
        no_of_conflicts *= 1.5;
        no_of_learnts *= 1.1;
    }

    this->cancelUntil(0);
    return status == TRUE;
}

lbool Solver::search(int no_of_conflicts, int no_of_learnts, SearchParams params) {
    int conflictC = 0;
    this->var_decay = 1 / params.var_decay;
    this->cla_decay = 1 / params.cla_decay;
    this->model->clear();

    while (1) {
        Constr *confl = this->propagate();
        if (confl != nullptr) {
            // conflict
            conflictC++;
            Vector<lit> *learnt_clause = new Vector<lit>();
            int *backtrack_level;
            if (decisionLevel() == root_level)
                return FALSE;
            this->analyze(confl, learnt_clause, backtrack_level);
            this->cancelUntil(std::max(*backtrack_level, root_level));
            this->record(learnt_clause);
            this->decayActivities();
        } else {
            // no conflict
            if (this->decisionLevel() == 0)
                this->simplifyDB(); // simplify the set of problem clauses: our simplifier cannot return false here
            
            if (this->nLearnts() - this->nAssigns() >= no_of_learnts)
                this->reduceDB(); // reduce the set of learnt clauses
            
            if (this->nAssigns() == this->nVars()) {
                // model found
                this->model->growTo(this->nVars());
                for (int i = 0; i < this->nVars(); i++)
                    (*(this->model))[i] = (value(i) == TRUE);
                this->cancelUntil(this->root_level);
                return TRUE;
            } else if (conflictC >= no_of_conflicts) {
                // reached bound on number of conflicts:
                this->cancelUntil(this->root_level); // force a restart
                return NOTHING;
            } else {
                // new variable decision:
                lit p = lit(this->order->select()); // may have heuristic for polarity here
                this->assume(p); // cannot return false here
            }
        }
    }
}