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

std::vector<double> ScaleFreeGraph::getProbabilities(int fromFirst) {
    std::vector<double> probabilities(fromFirst);

    int sumDegree = 0;
    for (int vertex = 0; vertex < fromFirst; vertex++) {
        int degree = this->getDegree(vertex);
        sumDegree += degree;
        probabilities[vertex] = degree;
    }

    for (int vertex = 0; vertex < fromFirst; vertex++) {
        probabilities[vertex] /= sumDegree;
    }

    return probabilities;
}

int chooseRandomWeighted(std::vector<double> &probabilites) {
    std::discrete_distribution<int> dist(probabilites.begin(), probabilites.end());
    std::random_device dev;
    std::mt19937 gen(dev());
    return dist(gen);
}

std::vector<int> ScaleFreeGraph::chooseRandomVertices(int fromFirst) {
    std::vector<int> vertices;
    std::vector<double> probabilities = this->getProbabilities(fromFirst);

    for (int idx = 0; idx < this->M; idx++) {
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
        if (vertex == this->M) {
            connectTo = std::vector<int>(this->M);
            std::iota(connectTo.begin(), connectTo.end(), 0);
        }
        std::cout << vertex << ":";
        for (int neighbour : connectTo) {
            std::cout << " " << neighbour;
            this->addEdge(vertex, neighbour);
        }
        std::cout << "\n";
    }
}