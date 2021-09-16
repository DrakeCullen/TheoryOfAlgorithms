#ifndef GRAPH_H
#define GRAPH_H

#include "PriorityQueue.h"
#include "../src/PriorityQueue.cpp"
#include "AdjacencyList.h"
#include "../src/AdjacencyList.cpp"

template <typename T> class Graph {
private:
	bool* visited;
	AdjacencyList<T> adj;
    int size;
	
public:
    Graph(int newSize);

	void addEdge(int vertex1, int vertex2, int weight = 0);
	
    void print();

};

#endif