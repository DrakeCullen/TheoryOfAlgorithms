#ifndef GRAPH_H
#define GRAPH_H


#include "AdjacencyList.h"
#include "../src/AdjacencyList.cpp"

#include <fstream>
#include <sstream>

template <typename T> class Graph {
private:
	AdjacencyList<T> adj;
    int currentSize;
    // Make dynamic later
    Node<T> cities[128];
	
public:
    Graph();

	void addEdge(int vertex1, int vertex2, string data, int weight = 0);

    void readInput(string filename);

    void MST(int startIndex = 0);

    void printMST(Node<T> ordering[]);
	
    void print();

};

#endif