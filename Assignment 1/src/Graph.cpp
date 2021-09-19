/**
    CSCI-480 - Assignment 1
    @file Graph.cpp
    @author Drake Cullen
*/

#include "../include/Graph.h"

template<typename T> 
Graph<T>::Graph() {
	currentSize = 0;
	//visited = new bool[size];
}

template<typename T> 
void Graph<T>::addEdge(int vertex1, int vertex2, string data, int weight) 
{ 
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->index = vertex2;
	newNode->weight = weight;
	newNode->from = vertex1;
	adj.addEdge(vertex1, newNode);
}

template<typename T> 
void Graph<T>::readInput(string filename)
{
	ifstream input(filename);
	string comments, cityInfo, cityName;
	int distance;
	getline(input, comments);
	getline(input, comments);
	
	for (unsigned int i = 0; i < 128; i++)
	{
		if (i > 1)
			getline(input, cityInfo);
		getline(input, cityInfo);
		stringstream ss(cityInfo);
		getline(ss, cityName, '[');
		Node<T> newCity;
		newCity.data = cityName;
		newCity.index = i;
		cities[i] = newCity;


		for (int j = 0; j < i; j++)
		{
			input >> distance;
			addEdge(i, j, cities[j].data, distance);
			addEdge(j, i, cities[i].data, distance);
		}
		adj.calculateSize();
		currentSize++;
	}
	input.close();
}

template<typename T> 
void Graph<T>::MST(int startIndex)
{
	PriorityQueue<Node<T>> pq(currentSize);
	bool visited[currentSize];
	int totalDistance = 0;
	Node<T> ordering[currentSize];
	int i = 0;
	
	for (unsigned int i = 0; i < currentSize; i++)
		visited[i] = 0;
	
	Node<T> lastCity = cities[startIndex];
	lastCity.weight = 0;
	lastCity.from = lastCity.index;

	pq.push(lastCity);
	while (pq.getSize() > 0)
	{
		Node<T> currentCity = pq.pop();
		visited[currentCity.index] = 1;
		currentCity.from = lastCity.index;
		totalDistance += currentCity.weight;
		ordering[i++] = currentCity;
		lastCity = currentCity;

		adj.checkNeighbors(visited, pq, currentCity.index);
	}
	cout<<"The total distance is: "<<totalDistance<<endl;
	printMST(ordering);
}

template<typename T> 
void Graph<T>::printMST(Node<T> ordering[])
{
	for (unsigned int i = 0; i < currentSize; i++)
		cout<<cities[ordering[i].from].data<<" to "<<ordering[i].data<<" \"distance = "<<ordering[i].weight<<'"'<<endl;

}

template<typename T> 
void Graph<T>::print() 
{
	adj.print();
}

