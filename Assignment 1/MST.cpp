/**
    CSCI-480 - Assignment 1
    @file MST.cpp
    @author Drake Cullen
*/

#include "./include/Graph.h"
#include "./src/Graph.cpp"

int main() {
    Graph<string> g;
    g.readInput("distances.txt");
    //g.print();
    g.MST(115);
    //g.dijkstra(13, 67);
}