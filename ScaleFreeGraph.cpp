//
// Created by jakubd on 9.10.2023.
//

#include "ScaleFreeGraph.h"

ScaleFreeGraph::ScaleFreeGraph(int N, int M) {
    this->N = N;
    this->M = M;

    this->degrees.resize(N);
    this->adj.resize(N);
}

int ScaleFreeGraph::getDegree(int vertex) {
    if (vertex < 0 || vertex >= (int)this->adj.size())
        return -1;

    return (int)this->adj[vertex].size();
}

std::vector<std::pair<double, int>> ScaleFreeGraph::getProbabilities(int fromFirst) {
    std::vector<std::pair<double, int>> probabilities(fromFirst);

    int sumDegree = 0;
    for (int vertex = 0; vertex < fromFirst; vertex++) {
        int degree = this->getDegree(vertex);
        sumDegree += degree;
        probabilities[vertex] = {degree, vertex};
    }

    for (int vertex = 0; vertex < fromFirst; vertex++) {
        if (sumDegree == 0)
            probabilities[vertex].first = 0;
        else
            probabilities[vertex].first /= sumDegree;
    }

    return probabilities;
}

int chooseRandomWeighted(std::vector<std::pair<double, int>> &probabilites) {

}

std::vector<int> ScaleFreeGraph::chooseRandomVertices(int fromFirst) {
    std::vector<int> vertices;
    std::vector<std::pair<double, int>> probabilities = this->getProbabilities(fromFirst);

    for (int idx = 0; idx < fromFirst; idx++) {
        int vertex = chooseRandomWeighted(probabilities);
        vertices.push_back(vertex);
    }

    return vertices;
}

void ScaleFreeGraph::addEdge(int vertex1, int vertex2) {
    this->adj[vertex1].push_back(vertex2);
    this->adj[vertex2].push_back(vertex1);
}

void ScaleFreeGraph::generateBAModel() {
    for (int vertex = this->M; vertex < this->N; vertex++) {
        std::vector<int> connectTo = this->chooseRandomVertices(vertex);

        for (int neighbour : connectTo) {
            this->addEdge(vertex, neighbour);
        }
    }
}