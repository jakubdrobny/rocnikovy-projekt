#include <iostream>
#include <cryptominisat5/cryptominisat.h>
#include <chrono>

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

  	Graph* g = new Graph(N, M);
  	g->generateGraphBAModel();
    g->printGraph();

  	CNF cnf;
    cnf.loadFromGraph(g, 2);
	cnf.print();

    SATSolver solver;
    solver.new_vars(cnf.vars_num);
    //std::cout << "cnf.vars_num: " << cnf.vars_num << "\n";
    for (Clause clause : cnf.clauses) {
        std::vector<Lit> solverClause;
        for (Literal lit : clause.literals) {
            solverClause.push_back(lit.value < 0 ? Lit(-lit.value - 1, true) : Lit(lit.value - 1, false));
            //std::cout << solverClause.back().toInt() << "\n";
        }
        //std::cout << " clause\n";
        solver.add_clause(solverClause);
    }

    lbool ret = solver.solve();
    std::cout << "Solution is (" << (ret == l_True) << "): ";
    for (lbool varVal : solver.get_model()) {
        std::cout << (varVal == l_True) << " ";
    }
    std::cout << "\n";
}

void testChromaticBruteAndSAT() {
    std::cout << "Enter N (no. of nodes) and M (no. of vertices to sample): ";
    int N, M;
    std::cin >> N >> M;

    for (int i = 0; i < 20; i++) {
        Graph g(N, M);
        int chromaticBrute = g.chromaticNumberBrute(), chromaticSAT = g.chromaticNumberSAT();

        assert(chromaticBrute == chromaticSAT);
    }

    std::cout << "Test finished successfully.\n";
}

void benchmarkChromaticSAT() {
    std::cout << "Enter N (no. of nodes) and M (no. of vertices to sample): ";
    int N, M;
    std::cin >> N >> M;

    Graph g(N, M);
    g.generateGraphBAModel();
    auto start = std::chrono::steady_clock::now();
    int chromaticNumber = g.chromaticNumberSAT();
    auto end = std::chrono::steady_clock::now();

    g.printGraph();
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    std::cout << "The chromatic number of the given graph is " << chromaticNumber << "\n";
}

int main() {
  // basicFunctionalityShowcase();
  // graphToCnfTest();
  // testChromaticBruteAndSAT();
  benchmarkChromaticSAT();

  return 0;
}
