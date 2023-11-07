#include <bits/stdc++.h>

using namespace std;

struct HistoryEntry {
    int from;
    vector<int> to;
    
    HistoryEntry() {}
    HistoryEntry(int from): from(from) {}
    HistoryEntry(int from, vector<int> to): from(from), to(to) {}
};

struct History {
    int len = 0;
    vector<HistoryEntry> entries;

    void addEntry(HistoryEntry entry) {
        entries.push_back(entry);
        len++;
    }
};

struct Graph {
    int N, M;
    vector<vector<int>> adj;
    History history;
    
    Graph() {}
    Graph(int _N, int _M): N(_N), M(_M), adj(_N) {}
    
    void addEdge(int v, int u) {
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    int getDegree(int v) {
        return (int)adj[v].size();
    }

    void addEntry(HistoryEntry entry) {
        history.addEntry(entry);
    }

    vector<double> getProbabilities(int fromFirst) {
        vector<double> probabilities(fromFirst);

        int sumDegree = 0;
        for (int vertex = 0; vertex < fromFirst; vertex++) {
            int degree = getDegree(vertex);
            sumDegree += degree;
            probabilities[vertex] = degree;
        }

        for (int vertex = 0; vertex < fromFirst; vertex++) {
            probabilities[vertex] /= sumDegree;
        }

        return probabilities;
    }

    int chooseRandomWeighted(vector<double> &probabilities) {
        discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
        random_device dev;
        mt19937 gen(dev());
        return dist(gen);
    }

    vector<int> sampleMVertices(int fromFirst) {
        vector<int> vertices;
        vector<double> probabilities = getProbabilities(fromFirst);

        for (int idx = 0; idx < M; idx++) {
            int vertex = chooseRandomWeighted(probabilities);
            vertices.push_back(vertex);
        }

        return vertices;
    }

    void generateGraphBAModel() {
        for (int vertexNo = M; vertexNo < N; vertexNo++) {
            vector<int> newNeighbours = sampleMVertices(vertexNo);

            if (vertexNo == M) {
                newNeighbours = vector<int>(M);
                iota(newNeighbours.begin(), newNeighbours.end(), 0);
            }

            addEntry(HistoryEntry(vertexNo, newNeighbours));
            for (int newNeighbour : newNeighbours) {
                addEdge(vertexNo, newNeighbour);
            }
        }
    }

    void printGraph() {
        cout << N << "\n";
        for (int i = 0; i < N; i++) {
            for (int x : adj[i]) {
                cout << i << " " << x << "\n";
            }
        }
    }

    int firstFitColoring() {
        vector<int> color(N, -1);
        for (int i = 0; i < M; i++) color[i] = 1;

        for (HistoryEntry entry : history.entries) {
            set<int> neighbourColors;
            for (int neighbour : entry.to)
                neighbourColors.insert(color[neighbour]);
            int newColor = 1;
            while (neighbourColors.count(newColor))
                newColor++;
            color[entry.from] = newColor;
        }

        return *max_element(color.begin(), color.end());
    }

    void colorRecursively(int vertexNo, vector<int> &color, int &ans) {
        if (vertexNo == N) {
            ans = min(ans, *max_element(color.begin(), color.end()));
            return;
        } else {
            set<int> neighbourColors;
            for (int neighbour : adj[vertexNo])
                neighbourColors.insert(color[neighbour]);
            for (int newColor = 1; newColor <= N - M + 1; newColor++) {
                if (!neighbourColors.count(newColor)) {
                    color[vertexNo] = newColor;
                    colorRecursively(vertexNo + 1, color, ans);
                    color[vertexNo] = -1;
                }
            }
        }
    }

    int chromaticNumber() {
        int ans = N + 1;
        vector<int> color(N, -1);
        for (int i = 0; i < M; i++)
            color[i] = 1;
        colorRecursively(M, color, ans);
        return ans;
    }
};

int main() {
    int N, M; cin >> N >> M;

    assert(N >= M);

    for (int i = 0; i < 100; i++) {
        Graph g(N, M);
        g.generateGraphBAModel();
        // g.printGraph();
        int greedyK = g.firstFitColoring(), optimalK = g.chromaticNumber();

        if (greedyK != optimalK) {
            cout << "greedy no. of colors: " << greedyK << "\n";
            cout << "optimal no. of colors: " << optimalK << "\n";
        }

        assert(greedyK >= optimalK);
    }

    return 0;
}