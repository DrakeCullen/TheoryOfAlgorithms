#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"
#include "LinkedList.cpp"
#include "Queue.h"
#include "Queue.cpp"

template <typename T> class Graph {
private:
	bool* visited;
	LinkedList<T>* adj;
    int size;
	
public:
    Graph(int newSize);

	void addEdge(int v1, int v2, int w=0);
	
    void print();
	
	void bfs(int s);
};

#endif