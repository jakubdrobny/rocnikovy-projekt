#include <iostream>

#include "Graph.h"
#include "CNF.h"
#include "assert.h"

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

  	CNF cnf(g);
	cnf.print();
}

int main() {
  // basicFunctionalityShowcase();
  graphToCnfTest();

  return 0;
}
