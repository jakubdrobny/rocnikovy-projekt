#include "CNF.h"
#include "Claus.h"
#include "Literal.h"
#include "Edge.h"
#include "assert.h"
#include <algorithm>
#include <set>

void CNF::loadFromGraph(Graph* g, int K) {
    // phase 1: 
    //   - for each of K colors, add clause with one literal for each node
    for (int node = 0; node < g->N; node++) {
        Claus clause;
        for (int color = 1; color <= K; color++) {
            clause.addLiteral(Literal(node, color, K));
        }
        this->addClause(clause);
    }

    // phase 2:
    //   - for each node, add clause X_ij => ~X_ik, where i is node and j, k are colors
    //   x => y <=> ~x or y  ....  ~X_ij or ~X_ik
    for (int node = 0; node < g->N; node++) {
        for (int color1 = 1; color1 <= K; color1++) {
            for (int color2 = 1; color2 <= K; color2++) {
                // useless clause
                if (color1 == color2)
                    continue;

                Claus clause;
                clause.addLiteral(Literal(node, color1, K, true));
                clause.addLiteral(Literal(node, color2, K, true));
                this->addClause(clause);
            }
        }
    }

    // phase 3:
    //   - for each edge from i to j, add clause X_ik => ~X_jk, where k is color
    std::set<std::pair<int, int>> set_edges;
    for (Edge edge : g->edges) {
        if (set_edges.count(std::make_pair(std::min(edge.from, edge.to), std::max(edge.from, edge.to))))
            continue;
        for (int color = 1; color <= K; color++) {
            Claus clause;
            clause.addLiteral(Literal(edge.from, color, K, true));
            clause.addLiteral(Literal(edge.to, color, K, true));
            this->addClause(clause);
        }
    }

    // break symmetries - assign some pair of vertices two colors
    assert(!g->edges.empty());

    Edge edge = g->edges[0];

    Claus clause;
    clause.addLiteral(Literal(edge.from, 1, K));
    clause.addLiteral(Literal(edge.to, 1, K));
    this->addClause(clause);
}

void CNF::addClause(Claus clause) {
    for (Literal lit : clause.literals)
        this->vars_num = std::max(this->vars_num, std::abs(lit.value));
    this->clauses.push_back(clause);
}

void CNF::print() {
    for (Claus clause : this->clauses) {
        clause.print();
    }
}