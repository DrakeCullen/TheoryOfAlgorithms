#ifndef GRAPH_H
#define GRAPH_H

#include "PriorityQueue.h"
#include "PriorityQueue.cpp"
#include "ResizableArray.h"
#include "ResizableArray.cpp"

template <typename T> class Graph {
private:
	bool* visited;
	ResizableArray<LinkedList<T>> adj;
    int size;
	
public:
    Graph(int newSize);

	void addEdge(int v1, int v2, int w=0);
	
    void print();
};

#endif