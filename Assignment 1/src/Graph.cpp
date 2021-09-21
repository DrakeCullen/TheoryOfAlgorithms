/**
    CSCI-480 - Assignment 1
    @file Graph.cpp
    @author Drake Cullen
*/

#include "../include/Graph.h"

Graph::Graph()
{
	currentSize = 0;
}

void Graph::readCities(istream &input, int i, bool &validInput)
{
	string cityInfo, cityName;
	if (i > 1)
		getline(input, cityInfo);
	getline(input, cityInfo);
	stringstream ss(cityInfo);
	if (cityInfo[0] == '*')
	{
		validInput = false;
		return;
	}
	getline(ss, cityName, '[');
	Node newCity;
	newCity.data = cityName;
	newCity.index = i;
	cities.insert(i, newCity);
}

 
void Graph::readDistances(istream &input, int i)
{
	int distance;
	for (int j = 0; j < i; j++)
	{
		input >> distance;
		addEdge(i, j, cities.getElement(j)->data, distance);
		addEdge(j, i, cities.getElement(i)->data, distance);
	}
}

 
void Graph::addEdge(int vertex1, int vertex2, string data, int weight) 
{ 
	Node* newNode = new Node;
	newNode->data = data;
	newNode->index = vertex2;
	newNode->weight = weight;
	newNode->from = vertex1;
	adj.addEdge(vertex1, newNode);
}

 
void Graph::readInput(string filename)
{
	ifstream input(filename);
	string comments;
	getline(input, comments);
	getline(input, comments);
	//Make work on any size file
	bool validInput = true;
	int i = 0;
	while (true)
	{
		readCities(input, i, validInput);
		if (!validInput)
			break;
		readDistances(input, i);
		currentSize++;
		i++;
	}
	input.close();
}

int Graph::findCityIndex(string city)
{
	for (int i = 0; i < currentSize; i++)
		if (cities.getElement(i)->data == city)
			return i;
	return -1;
}

void Graph::MST(int startIndex)
{
	
	int totalDistance = 0, index = 0;
	PriorityQueue<Node> pq;
	bool visited[currentSize];
	Node ordering[currentSize];
	for (int i = 0; i < currentSize; i++)
		visited[i] = 0;
	
	Node firstCity = *cities.getElement(startIndex);
	firstCity.weight = 0;
	firstCity.from = firstCity.index;
	
	pq.push(firstCity);
	while (pq.getSize() > 0)
	{
		Node currentCity = pq.pop();
		if (!visited[currentCity.index])
		{
			visited[currentCity.index] = 1;
			totalDistance += currentCity.weight;
			ordering[index++] = currentCity;
			adj.checkNeighbors(visited, pq, currentCity.index);
		}
		
	}
	cout<<"The total distance is: "<<totalDistance<<endl;
	printMST(ordering);
}

 
void Graph::printMST(Node ordering[])
{
	//Change from hard coded value
	for (int i = 0; i < 128; i++)
		cout<<cities.getElement(ordering[i].from)->data<<" to "<<ordering[i].data<<" \"distance = "<<ordering[i].weight<<'"'<<endl;

}

 
void Graph::dijkstra(int startIndex, int endIndex)
{
	const int INF = 2147483646;
	int distance[currentSize];
	bool visited[currentSize];
	int prev[currentSize];
	PriorityQueue<Node> pq;
	for (int i = 0; i < currentSize; i++)
	{
		distance[i] = INF;
		visited[i] = 0;
	}
	
	distance[startIndex] = 0;	
	visited[startIndex] = 0;
	Node firstCity = *cities.getElement(startIndex);
	firstCity.weight = 0;
	firstCity.from = firstCity.index;

	pq.push(firstCity);
	while (pq.getSize() > 0)
	{
		Node currentCity = pq.pop();
		visited[currentCity.index] = 1;
		adj.checkShortestPath(visited, pq, currentCity.index, distance, prev);
	}
	printDijkstra(prev, distance, startIndex, endIndex);
}

 
void Graph::printDijkstra(int prev[], int distances[], int startIndex, int endIndex)
{
	int lastWeight = 0, numberOfCities = 0, copyEnd = endIndex;

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

	cout << "1: "<< cities.getElement(startIndex)->data << " to " << cities.getElement(path[0])->data << " \"distance = " << distances[path[0]] << "\"" << endl;
	lastWeight = distances[path[0]];
	for (int i = 0; i < numberOfCities - 1; i++)
	{
		cout << i + 2 << ": "<< cities.getElement(path[i])->data << " to " << cities.getElement(path[i+1])->data << " \"distance = " << distances[path[i+1]] - lastWeight << "\"" << endl;
		lastWeight = distances[path[i+1]];
	}
	cout<<"Total distance: "<<distances[endIndex]<<endl;
}