#include "Graph.h"

#include <random>
#include <iostream>
#include <algorithm>
#include <set>
#include <chrono>
#include "assert.h"

void Graph::addEdge(int v, int u) {
    assert(0 <= v && v <= (int)this->adj.size());
    assert(0 <= u && u <= (int)this->adj.size());

    this->adj[v].push_back(u);
    this->adj[u].push_back(v);

    this->edges.push_back(Edge(u, v));
}

int Graph::getDegree(int v) {
    return (int)this->adj[v].size();
}

void Graph::addEntry(HistoryEntry entry) {
    this->history.addEntry(entry);
}

std::vector<double> Graph::getProbabilities(int fromFirst) {
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

int Graph::chooseRandomWeighted(std::vector<double> &probabilities) {
    std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
    std::random_device dev;
    std::mt19937 gen(dev());
    return dist(gen);
}

std::vector<int> Graph::sampleMVertices(int fromFirst) {
    std::vector<int> vertices;
    std::vector<double> probabilities = this->getProbabilities(fromFirst);

    for (int idx = 0; idx < M; idx++) {
        int vertex = this->chooseRandomWeighted(probabilities);
        vertices.push_back(vertex);
    }

    return vertices;
}

void Graph::generateGraphBAModel() {
    for (int vertexNo = this->M; vertexNo < this->N; vertexNo++) {
        std::vector<int> newNeighbours = this->sampleMVertices(vertexNo);

        if (vertexNo == this->M) {
            newNeighbours = std::vector<int>(this->M);
            iota(newNeighbours.begin(), newNeighbours.end(), 0);
        }

        this->addEntry(HistoryEntry(vertexNo, newNeighbours));
        for (int newNeighbour : newNeighbours) {
            addEdge(vertexNo, newNeighbour);
        }
    }
}

void Graph::printGraph() {
    std::cout << this->N << "\n";
    for (int i = 0; i < this->N; i++) {
        for (int x : this->adj[i]) {
            std::cout << i << " " << x << "\n";
        }
    }
}

int Graph::firstFitColoring() {
    std::vector<int> color(this->N, -1);
    for (int i = 0; i < this->M; i++) color[i] = 1;

    for (HistoryEntry entry : this->history.entries) {
        std::set<int> neighbourColors;
        for (int neighbour : entry.to)
            neighbourColors.insert(color[neighbour]);
        int newColor = 1;
        while (neighbourColors.count(newColor))
            newColor++;
        color[entry.from] = newColor;
    }

    return *max_element(color.begin(), color.end());
}

void Graph::colorRecursively(int vertexNo, std::vector<int> &color, int &ans) {
    if (vertexNo == this->N) {
        ans = std::min(ans, *max_element(color.begin(), color.end()));
        return;
    } else {
        std::set<int> neighbourColors;
        for (int neighbour : this->adj[vertexNo])
            neighbourColors.insert(color[neighbour]);
        for (int newColor = 1; newColor <= this->N - this->M + 1; newColor++) {
            if (!neighbourColors.count(newColor)) {
                color[vertexNo] = newColor;
                colorRecursively(vertexNo + 1, color, ans);
                color[vertexNo] = -1;
            }
        }
    }
}

int Graph::chromaticNumberBrute() {
    int ans = this->N + 1;
    std::vector<int> color(this->N, -1);
    for (int i = 0; i < this->M; i++)
        color[i] = 1;
    colorRecursively(this->M, color, ans);
    return ans;
}

int Graph::getRandom(int right) {
    std::uniform_int_distribution<> dist{0, right};
    std::random_device dev;
    std::mt19937 gen(dev());

    return dist(gen);
}

std::vector<int> Graph::getPermutationsOfVertices() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rnd(seed);

    std::vector<int> permutation(this->N); iota(permutation.begin(), permutation.end(), 0);
    shuffle(permutation.begin(), permutation.end(), rnd);

    return permutation;
}

History Graph::createHistoryFromPermutation(std::vector<int> vertices) {
    History history;

    std::vector<int> seen(this->N);
    for (int vertexNo : vertices) {
        HistoryEntry entry(vertexNo);
        for (int neighbour : this->adj[vertexNo]) {
            if (seen[neighbour]) {
                entry.add(neighbour);
            }
        }
        history.addEntry(entry);
        seen[vertexNo] = 1;
    }

    return history;
}

void Graph::constructGraphFromHistory(History history) {
    for (HistoryEntry entry : history.entries) {
        for (int neighbour : entry.to) {
            this->addEdge(entry.from, neighbour);
        }
    }
}