#ifndef CNF_H
#define CNF_H

#include "Clause.h"
class Graph;

#include <vector>

class CNF {
    public:
        int vars_num;
        std::vector<Clause> clauses;

        void loadFromGraph(Graph *g, int K);
        void addClause(Clause clause);
        void print();
};

#include "Graph.h"

#endif