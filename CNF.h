#ifndef CNF_H
#define CNF_H

#include "Clause.h"
#include "Graph.h"

#include <vector>

class CNF {
    public:
        std::vector<Clause> clauses;
        
        CNF(Graph g, int K) {
            loadFromGraph(g, K);
        }

        void loadFromGraph(Graph g, int K);
        void addClause(Clause clause);
        void print();
};

#endif