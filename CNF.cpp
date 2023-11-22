#include "CNF.h"
#include "Clause.h"
#include "Literal.h"
#include "Edge.h"
#include <algorithm>

void CNF::loadFromGraph(Graph g, int K) {
    // phase 1: 
    //   - for each of K colors, add clause with one literal for each node
    for (int node = 0; node < g.N; node++) {
        for (int color = 1; color <= K; color++) {
            Clause clause;
            clause.addLiteral(Literal(node, color, K));
            this->addClause(clause);
        }
    }

    // phase 2:
    //   - for each node, add clause X_ij => ~X_ik, where i is node and j, k are colors
    //   x => y <=> ~x or y  ....  ~X_ij or ~(~X_ik) = X_ik
    for (int node = 0; node < g.N; node++) {
        for (int color1 = 1; color1 <= K; color1++) {
            for (int color2 = 1; color2 <= K; color2++) {
                // useless clause
                if (color1 == color2)
                    continue;

                Clause clause;
                clause.addLiteral(Literal(node, color1, K, true));
                clause.addLiteral(Literal(node, color2, K));
                this->addClause(clause);
            }
        }
    }

    // phase 3:
    //   - for each edge from i to j, add clause X_ik => ~X_jk, where k is color
    for (Edge edge : g.edges) {
        for (int color = 1; color <= K; color++) {
            Clause clause;
            clause.addLiteral(Literal(edge.from, color, K, false));
            clause.addLiteral(Literal(edge.to, color, K));
            this->addClause(clause);
        }
    }
}

void CNF::addClause(Clause clause) {
    for (Literal lit : clause.literals)
        this->vars_num = std::max(this->vars_num, std::abs(lit.value));
    this->clauses.push_back(clause);
}

void CNF::print() {
    for (Clause clause : this->clauses) {
        clause.print();
    }
}