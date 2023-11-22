#include <iostream>
#include <cryptominisat5/cryptominisat.h>

#include "Graph.h"
#include "CNF.h"
#include "Clause.h"
#include "assert.h"

using namespace CMSat;

void basicFunctionalityShowcase() {
	int N, M;
	std::cin >> N >> M;

	assert(N >= M);

	for (int i = 0; i < 20; i++) {
		Graph g(N, M);
		g.generateGraphBAModel();
		// g.printGraph();
		int greedyK = g.firstFitColoring(), optimalK = g.chromaticNumberBrute();

		std::cout << "greedy no. of colors: " << greedyK << "\n";
		std::cout << "optimal no. of colors: " << optimalK << "\n";

		for (int j = 0; j < 20; j++) {
			Graph g2(N, M, g.createHistoryFromPermutation(g.getPermutationsOfVertices()));
			int permutationGreedyK = g2.firstFitColoring();
			std::cout << "permutation greedy no. of colors: " << permutationGreedyK << "\n";
		}

		assert(greedyK >= optimalK);

		std::cout << "\n\n";
	}
}

void graphToCnfTest() {
  	int N, M;
  	std::cin >> N >> M;

  	assert(N >= M);

  	Graph g(N, M);
  	g.generateGraphBAModel();

  	CNF cnf(g, 3);
	cnf.print();

    SATSolver solver;
    solver.new_vars(cnf.vars_num);
    std::cout << cnf.vars_num << "\n";
    for (Clause clause : cnf.clauses) {
        std::vector<Lit> solverClause;
        for (Literal lit : clause.literals)
            solverClause.push_back(lit.value < 0 ? Lit(-lit.value, true) : Lit(lit.value, false));
        solver.add_clause(solverClause);
    }

    lbool ret = solver.solve();
    std::cout << "Solution is (" << (ret == l_True) << "): ";
    for (lbool varVal : solver.get_model()) {
        std::cout << (varVal == l_True) << " ";
    }
    std::cout << "\n";
}

int main() {
  // basicFunctionalityShowcase();
  graphToCnfTest();

  return 0;
}
