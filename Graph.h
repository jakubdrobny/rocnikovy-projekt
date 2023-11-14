#ifndef Graph_H
#define Graph_H

#include "History.h"
#include "HistoryEntry.h"

#include <vector>

class Graph {
    public:
        int N, M;
        std::vector<std::vector<int>> adj;
        History history;
        
        Graph() {}
        Graph(int _N, int _M): N(_N), M(_M), adj(_N) {}
        Graph(int _N, int _M, History _history): N(_N), M(_M), adj(_N), history(_history) {
            constructGraphFromHistory(_history);
        }
        
        void addEdge(int v, int u);
        int getDegree(int v);
        void addEntry(HistoryEntry entry);
        std::vector<double> getProbabilities(int fromFirst);
        int chooseRandomWeighted(std::vector<double> &probabilities);
        std::vector<int> sampleMVertices(int fromFirst);
        void generateGraphBAModel();
        void printGraph();
        int firstFitColoring();
        void colorRecursively(int vertexNo, std::vector<int> &color, int &ans);
        int chromaticNumberBrute();
        int getRandom(int right);
        std::vector<int> getPermutationsOfVertices();
        History createHistoryFromPermutation(std::vector<int> vertices);
        void constructGraphFromHistory(History history);
};

#endif