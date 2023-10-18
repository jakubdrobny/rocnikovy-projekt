#include "ScaleFreeGraph.h"

int main() {
    ScaleFreeGraph g(10, 5);
    int greedyK = g.generateBAModel();
    std::cout << greedyK << "\n";
}