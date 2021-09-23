/**
    CSCI-480 - Assignment 1
    @file Graph.cpp
    @author Drake Cullen
	Create a graph using an adjacency list. Can read in data, find MST, and find the single source shortest path,
*/

#include "../include/Graph.h"
#include <chrono>

/**
 * Default constructor. Initialize the size to 0.
 * O(1)
 */
Graph::Graph()
{
	currentSize = 0;
}

/**
 * Read in the line containing city information. Extract the cities name.
 * @param istream - The form of input
 * @param int - The i'th word being read in. Used to know when to take in an extra newline character
 * @param bool - Keeps track of when we are at the end of a file
 */
void Graph::readCities(istream &input, int i, bool &validInput)
{
	string cityInfo, cityName;

	// Grab the extra newline character
	if (i > 1)
		getline(input, cityInfo);
	
	getline(input, cityInfo);
	stringstream ss(cityInfo);

	// If a comment is spotted, we know were at the end of the input
	if (cityInfo[0] == '*')
	{
		validInput = false;
		return;
	}

	// Grab all the text before the [ symbol
	getline(ss, cityName, '[');

	// Create a city and add it to the resizable cities array
	City newCity;
	newCity.data = cityName;
	newCity.index = i;
	cities.insert(newCity);
}

/**
 * Read in the distances associated with a city
 * For example, if this is the 5th city, we will read in 4 distances
 * @param istream - The form of input
 * @param int - The i'th word being read in
 */
void Graph::readDistances(istream &input, int i)
{
	int distance;
	for (int j = 0; j < i; j++)
	{
		input >> distance;
		// The graph is undirected, so add adges in both directions
		addEdge(i, j, cities.getElement(j)->data, distance);
		addEdge(j, i, cities.getElement(i)->data, distance);
	}
}

/**
 * Create a new instance of a city and add it to the adjacency list.
 * @param int - The index of the first city. We will add the second city to the list containing connections to the first city
 * @param int - The index of the second city
 * @param string - The name of the second city
 * @param int - The distance (weight) between the two cities
 * O(log(n)). Every operation is constant, except for the calculateSize method, which has an average time of log(n).
 */
void Graph::addEdge(int city1, int city2, string name, int weight) 
{ 
	City* newCity = new City;
	newCity->data = name;
	newCity->index = city2;
	newCity->weight = weight;
	newCity->from = city1;

	// Make sure there is enough space in the adjacency list. If not, increase the size
	adjacencyList.calculateSize();

	// Get a pointer to the linked list that contains the neighbors of city1
    LinkedList<City>* city1Neighbors = adjacencyList.getElement(city1);
    city1Neighbors->push(newCity);
}

/**
 * Handles reading in the input. Calls readCities and readDistances.
 * @param string - The name of the file you would like to read
*/ 
void Graph::readInput(string filename)
{
	ifstream input(filename);
	string comments;
	getline(input, comments);
	getline(input, comments);
	bool validInput = true;
	int i = 0;

	// Read in cities and distances until we reach the comment at the end of the file.
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

/**
 * Given a cities name, find its index by using the cities array.
 * @param string - The name of the city you are looking for
 * @return int - The index of the city, or -1 if the city isn't found
 * O(n) where n is the number of vertices in the graph
 */
int Graph::findCityIndex(string city)
{
	for (int i = 0; i < currentSize; i++)
		if (cities.getElement(i)->data == city)
			return i;
	return -1;
}

/**
 * Given a starting node, find the minimum spanning tree of the graph.
 * Add an initial city to the tree, and get the top element from the priority queue until it is empty.
 * If the city hasn't been visited, add its weight and check its neighbors
 * @param int - The index of the start city
 * O(E*log(V)) where E is the number of edges and V is the number of cities
 */
void Graph::MST(int startIndex)
{
	// Used to check the speed of the method
	auto start = chrono::steady_clock::now();
	// Stores the distance traveled and index keeps track of the position in the ordering array
	int totalDistance = 0, index = 0;
	PriorityQueue<City> pq;
	// Keep track of the visited cities
	bool visited[currentSize];
	// Stores the cities in the order they are visited so they can be printed later
	City ordering[currentSize];

	// Initialize visited so that all cities are unvisited
	for (int i = 0; i < currentSize; i++)
		visited[i] = 0;
	
	// Add the initial city to the priority queue
	City firstCity = *cities.getElement(startIndex);
	firstCity.weight = 0;
	firstCity.from = firstCity.index;
	pq.push(firstCity);

	// Repeats for every edge in the graph. O(E)
	while (pq.getSize() > 0)
	{
		// O(log(V) to get the top element and rearrange the min heap
		City currentCity = pq.pop();

		// The cities connecting to a certain city are only explored one time
		if (!visited[currentCity.index])
		{
			visited[currentCity.index] = 1;
			totalDistance += currentCity.weight;
			ordering[index++] = currentCity;

			LinkedList<City>* cityNeighbors = adjacencyList.getElement(currentCity.index);
    		cityNeighbors->addUnvisitedNeighborsToQueue(visited, pq);
		}
	}

	// Find the ending time and call the method to print the results
	auto end = chrono::steady_clock::now();
	double timeTaken = double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000000;
	cout << "The total distance is: " << totalDistance << endl;
	printMST(ordering, timeTaken);
}

/**
 * Print the MST in the order the nodes were visited. Print out the time taken at the end.
 * @param City[] - The array containing the order in which cities were visited
 * O(V) where V is the number of cities in the graph
 */
void Graph::printMST(City ordering[], double timeTaken)
{
	for (int i = 0; i < currentSize; i++)
		cout << cities.getElement(ordering[i].from)->data << " to "<<ordering[i].data << " \"distance = " << ordering[i].weight << '"' << endl;
	cout << "\nTime taken to find the Minimum Spanning Tree: " << timeTaken << " seconds. \n";
}

// SHOULD DIJKSTRA HAVE VISITED?????
void Graph::dijkstra(int startIndex, int endIndex)
{
	auto start = chrono::steady_clock::now();
	const int INF = 2147483646;
	int distance[currentSize];
	bool visited[currentSize];
	int prev[currentSize];
	PriorityQueue<City> pq;
	for (int i = 0; i < currentSize; i++)
	{
		distance[i] = INF;
		visited[i] = 0;
	}
	
	distance[startIndex] = 0;	
	visited[startIndex] = 0;
	City firstCity = *cities.getElement(startIndex);
	firstCity.weight = 0;
	firstCity.from = firstCity.index;

	pq.push(firstCity);
	while (pq.getSize() > 0)
	{
		City currentCity = pq.pop();
		visited[currentCity.index] = 1;
		LinkedList<City>* temp = adjacencyList.getElement(currentCity.index);
    	temp->updateNeighborsForShorterPath(visited, pq, currentCity.index, distance, prev);
	}
	auto end = chrono::steady_clock::now();
	double timeTaken = double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000000;
	printDijkstra(prev, distance, startIndex, endIndex, timeTaken);
}

 
void Graph::printDijkstra(int prev[], int distances[], int startIndex, int endIndex, double timeTaken)
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
	cout << "\nTime taken to find the shortest path: " << timeTaken << " seconds. \n";
}