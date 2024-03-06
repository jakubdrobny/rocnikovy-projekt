#include <set>
#include <iostream>
#include <cryptominisat5/cryptominisat.h>
#include <chrono>
#include <fstream>
#include <numeric>

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

void createDataForFixedM() {
    std::cout << "Enter filename without extension (.csv) to store data: ";
    std::string filename; std::cin >> filename;
    filename += ".csv";
    std::cout << "Enter M (no. of initial vertices): ";
    int M; std::cin >> M;

    std::vector<int> x;
    std::vector<double> y;
    std::vector<int> min_y, max_y;

    for (int N = M + 5; N <= 100; N++) {
        std::cout << "Generating data for N=" << N << "...\n";
        std::vector<int> chromatic_numbers;
        
        for (int it = 0; it < 100; it++) {
            Graph g(N, M);
            g.generateGraphBAModel();
            chromatic_numbers.push_back(g.chromaticNumberSAT());
        }

        std::sort(chromatic_numbers.begin(), chromatic_numbers.end());

        x.push_back(N);
        int C = (int)chromatic_numbers.size();
        y.push_back(C % 2 ? chromatic_numbers[C / 2] : (double) (chromatic_numbers[C / 2] + chromatic_numbers[(C - 1) / 2]) / 2.);
        min_y.push_back(chromatic_numbers[0]);
        max_y.push_back(chromatic_numbers.back());

        std::cout << min_y.back() << " " << y.back() << " " << max_y.back() << "\n";
    }

    assert(x.size() == y.size());
    
    std::ofstream outputFile(filename);
    outputFile << "x;y;min_y;max_y\n";
    
    int ndata = (int)x.size();
    for (int i = 0; i < ndata; i++) {
        outputFile << x[i] << ";" << y[i] << ";" << min_y[i] << ";" << max_y[i] << "\n";
    }
    outputFile.close();
}

void testMinimalChromaticNumber() {
    std::cout << "Enter N (no. of nodes) and M (initial number of nodes): ";
    int N, M; std::cin >> N >> M;

    History h;
    std::vector<int> to(M);
    std::iota(to.begin(), to.end(), 0);
    for (int i = M; i < N; i++) {
        HistoryEntry he(i, to);
        h.addEntry(he);
    }

    Graph g(N, M);
    g.constructGraphFromHistory(h);
    int chromaticNumber = g.chromaticNumberSAT();
    std::cout << "Chromatic number is: " << chromaticNumber << "\n";
}

void testMaximalChromaticNumber() {
    std::cout << "Enter N (no. of nodes) and M (initial number of nodes): ";
    int N, M; std::cin >> N >> M;

    History h;
    std::vector<int> to(M);
    std::iota(to.begin(), to.end(), 0);
    for (int i = M; i < N; i++) {
        HistoryEntry he(i, to);
        h.addEntry(he);
        for (int &x : to)
            x++;
    }

    Graph g(N, M);
    g.constructGraphFromHistory(h);
    int chromaticNumber = g.chromaticNumberSAT();
    std::cout << "Chromatic number is: " << chromaticNumber << "\n";
}

int main() {
  // basicFunctionalityShowcase(); // using bruteforce for chromaticNo computation
  // graphToCnfTest();
  // testChromaticBruteAndSAT(); // N <= 9
  // benchmarkChromaticSAT(); // N <= 200 AND M <= 20
  // createDataForFixedM();
  // testMinimalChromaticNumber();
  testMaximalChromaticNumber();

  return 0;
}
