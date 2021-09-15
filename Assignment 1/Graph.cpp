#include "Graph.h"

template<typename T> 
Graph<T>::Graph(int newSize) {
	size = newSize;
	visited = new bool[size];
}

template<typename T> 
void Graph<T>::addEdge(int v1, int v2, int w) 
{ 
	Node<T>* newNode = new Node<T>;
	newNode->data = v2;
	//newNode->weight = w;
	adj.appendNode(0, newNode);
	//l.print();
	//adj.getAddress(0).push(2,1); 
	//adj[0]->print();//.push(newNode, 0); 
}

template<typename T> 
void Graph<T>::print() 
{
	for (int i = 0; i < size; i++) 
	{
		cout<<i<<": ";
		adj.getAddress(i).print();
	}
}
