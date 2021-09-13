#include "Graph.h"
#include "Graph.cpp"


int main() {
    Graph<int> g(13);
    g.addEdge(0, 9);
    g.addEdge(0, 1);
    g.addEdge(1, 8);
    g.addEdge(9, 8);
    g.addEdge(8, 7);
    g.addEdge(7, 10);
    g.addEdge(7, 11);
    g.addEdge(7, 3);
    g.addEdge(7, 6);
    g.addEdge(10, 11);
    g.addEdge(6, 5);
    g.addEdge(5, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 2);
    //g.print();
    g.bfs(0);
}