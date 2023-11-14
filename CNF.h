#ifndef CNF_H
#define CNF_H

#include "Clause.h"

#include <vector>

class CNF {
    public:
        std::vector<Clause> clauses;
        
        CNF() {}
};

#endif