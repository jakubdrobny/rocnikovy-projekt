#ifndef CNF_H
#define CNF_H

#include "Claus.h"
class Graph;

#include <vector>

class CNF {
    public:
        int vars_num = 0;
        std::vector<Claus> clauses;

        void loadFromGraph(Graph *g, int K);
        void addClause(Claus clause);
        void print();
};

#include "Graph.h"

#endif