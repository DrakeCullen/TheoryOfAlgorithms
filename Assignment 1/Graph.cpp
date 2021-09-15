#include "Graph.h"

template<typename T> 
Graph<T>::Graph(int newSize) {
	size = newSize;
	visited = new bool[size];
}

template<typename T> 
void Graph<T>::addEdge(int vertex1, int vertex2, int weight) 
{ 
	Node<T>* newNode = new Node<T>;
	newNode->data = vertex2;
	newNode->weight = weight;
	adj.calculateSize(vertex1, vertex2);
	adj.addEdge(vertex1, newNode);
}

template<typename T> 
void Graph<T>::print() 
{
	adj.print();
}

