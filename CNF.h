#ifndef CNF_H
#define CNF_H

#include "Clause.h"
#include "Graph.h"

#include <vector>

class CNF {
    public:
        std::vector<Clause> clauses;
        
        CNF(Graph g) {
            loadFromGraph(g);
        }

        void loadFromGraph(Graph g) {}
        void print() {}
};

#endif