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
	
	Node<T> firstCity = cities[startIndex];
	firstCity.weight = 0;
	firstCity.from = firstCity.index;

	pq.push(firstCity);
	while (pq.getSize() > 0)
	{
		Node<T> currentCity = pq.pop();
		if (!visited[currentCity.index])
		{
			visited[currentCity.index] = 1;
			totalDistance += currentCity.weight;
			ordering[i++] = currentCity;

			adj.checkNeighbors(visited, pq, currentCity.index);
		}
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
void Graph<T>::dijkstra(int startIndex, int endIndex)
{
	const int INF = 2147483646;
	int distance[currentSize];
	bool visited[currentSize];
	int prev[currentSize];
	PriorityQueue<Node<T>> pq(currentSize);
	for (unsigned int i = 0; i < currentSize; i++)
	{
		distance[i] = INF;
		visited[i] = 0;
	}
	
	distance[startIndex] = 0;	
	visited[startIndex] = 0;
	Node<T> firstCity = cities[startIndex];
	firstCity.weight = 0;
	firstCity.from = firstCity.index;

	pq.push(firstCity);
	while (pq.getSize() > 0)
	{
		Node<T> currentCity = pq.pop();
		visited[currentCity.index] = 1;
		adj.checkShortestPath(visited, pq, currentCity.index, distance, prev);
	}
	printDijkstra(prev, distance, startIndex, endIndex);
}

template<typename T> 
void Graph<T>::printDijkstra(int prev[], int distances[], int startIndex, int endIndex)
{
	int totalDistance = 0, lastWeight = 0, numberOfCities = 0, copyEnd = endIndex;

	while (copyEnd != startIndex)
	{
		copyEnd = prev[copyEnd];
		numberOfCities++;
	}

	copyEnd = endIndex;
	int path[numberOfCities];
	for (int i = numberOfCities - 1; i >= 0; i--)
	{
		path[i] = copyEnd;
		copyEnd = prev[copyEnd];
	}

	cout << "1: "<< cities[startIndex].data << " to " << cities[path[0]].data << " \"distance = " << distances[path[0]] << "\"" << endl;
	lastWeight = distances[path[0]];
	for (unsigned int i = 0; i < numberOfCities - 1; i++)
	{
		cerr << i + 2 << ": "<< cities[path[i]].data << " to " << cities[path[i+1]].data << " \"distance = " << distances[path[i+1]] - lastWeight << "\"" << endl;
		lastWeight = distances[path[i+1]];
	}
	cout<<"Total distance: "<<distances[endIndex]<<endl;
}

template<typename T> 
void Graph<T>::print() 
{
	adj.print();
}

