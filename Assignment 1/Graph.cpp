#include "Graph.h"

template<typename T> 
Graph<T>::Graph(int newSize) {
	size = newSize;
	visited = new bool[size];
	adj = new LinkedList<T>[size];
}

template<typename T> 
void Graph<T>::addEdge(int v1, int v2, int w) 
{ 
	Node<T>* newNode = new Node<T>;
	newNode->data = v2;
	newNode->weight = w;
	adj[v1].push(newNode); 
}

template<typename T> 
void Graph<T>::print() 
{
	for (int i = 0; i < size; i++) 
	{
		cout<<i<<": ";
		adj[i].print();
	}
}

template<typename T> 
void Graph<T>::bfs(int s) 
{
	Queue<T> queue;
	visited[s] = 1;
	queue.push(s);
	while(!queue.isEmpty()) 
	{
		int v = queue.pop();
		visited[v] = 1;
		cout<<v<<' ';
		adj[v].checkForAllElements(queue, visited);
	}
}
