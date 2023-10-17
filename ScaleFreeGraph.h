//
// Created by jakubd on 9.10.2023.
//

#ifndef CODE_SCALEFREEGRAPH_H
#define CODE_SCALEFREEGRAPH_H

#include <vector>
#include <random>
#include <iostream>

class ScaleFreeGraph {
public:
    ScaleFreeGraph(int N, int M);

    int N, M;
    std::vector<std::vector<int>> adj;
    std::vector<int> degrees;

    void generateBAModel();
    std::vector<int> chooseRandomVertices(int fromFirst);
    void addEdge(int vertex1, int vertex2);
    std::vector<double> getProbabilities(int fromFirst);
    int getDegree(int vertex);
};

#endif //CODE_SCALEFREEGRAPH_H
