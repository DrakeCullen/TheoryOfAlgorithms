#include "Graph.h"
#include "Graph.cpp"


int main() {
    Graph<int> g(13);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 20);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 4, 12);
    g.addEdge(3, 2, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 1);
    g.print();
}