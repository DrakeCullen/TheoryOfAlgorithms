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
 * @param int - The i'th city being read in
 */
void Graph::readDistances(istream &input, int i)
{
	int distance;
	for (int j = i - 1; j >= 0; j--)
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
 * O(1). Every operation is constant
 */
void Graph::addEdge(int city1, int city2, string name, int weight) 
{ 
	City* newCity = new City;
	newCity->data = name;
	newCity->index = city2;
	newCity->weight = weight;
	newCity->from = city1;

	// Make sure there is enough space in the adjacency list. If not, increase the size
	//adjacencyList.calculateSize();

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
 * O(V) where V is the number of cities in the graph
 */
int Graph::findCityIndex(string city)
{
	for (int i = 0; i < currentSize; i++)
		if (cities.getElement(i)->data == city)
			return i;
	return -1;
}

/**
 * Given a starting city, find the minimum spanning tree of the graph.
 * Add an initial city to the priority queue, and get the top element from the priority queue until it is empty.
 * If the city hasn't been visited, add its weight and check its neighbors
 * @param int - The index of the start city
 * O((V*log(V)) + E*log(V)) where E is the number of edges and V is the number of cities. Simplifying gives 
 * O(log(V)*(E+V))
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

	// This loop will be ran at a maximum of V times where V is the number of cities.
	while (pq.getSize() > 0 && index < currentSize)
	{
		// We know that popping from the min heap priority queue to get the city with the least distance takes O(log(V)) where V is the number of cities.
		// This operation happens for every city V. So we have O(V*log(V) 
		City currentCity = pq.pop();

		/** The statements in the 'if' statement are independent of the size of the priority queue because the 'if' statement limits them to be ran only for each city (each city is visited once).
		*   The runtime of the code in the 'if' statement is independent of the popping runtime (seen above), so the two runtimes will be added instead of multiplied.   
		*   Furthermore, by running the 'if' statement for each city, all possible Edges (E) will be explored.
		*   Within the if statement, every line has a constant runtime except for the addUnvisitedNeighborsToQueue method.
		*   More specifically, the addUnvisitedNeighborsToQueue method will end up looping through every adjacent edge to a city, and taking O(log(V)) to push to the priority queue.
		*   Therefore, by checking and pushing every edge that exists in the graph, we have the runtime O(E*log(V))
		*/
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
 * @param double - The time taken to run the algorithm
 * O(V) where V is the number of cities in the graph
 */
void Graph::printMST(City ordering[], double timeTaken)
{
	for (int i = 0; i < currentSize; i++)
		cout << cities.getElement(ordering[i].from)->data << " to "<<ordering[i].data << " \"distance = " << ordering[i].weight << '"' << endl;
	cout << "\nTime taken to find the Minimum Spanning Tree: " << timeTaken << " seconds. \n";
}

/**
 * Given a starting and ending city, find the shortest path between them.
 * Add the start city to the priority queue. Initialize all distances to INF except for the starting node.
 * While the priority queue still has cities, check there neighbors to see if you can update the minimum distance.
 * If so, add these cities to the queue and update their distances.
 * @param int - The index of the start city
 * @param int - The index of the end city
 * O((V*log(V)) + E*log(V)) where E is the number of edges and V is the number of cities. Simplifying gives 
 * O(log(V)*(E+V))
 */ 
void Graph::dijkstra(int startIndex, int endIndex)
{
	// Used to measure the time it takes to run the algorithm
	auto start = chrono::steady_clock::now();
	// Represent infinity with the maximum value and integer can store
	const int INF = 2147483646;
	// Arrays to keep track of the shortest distance to a city and whether the city has been visited
	int distance[currentSize];
	bool visited[currentSize];
	// Keep track of how we got to a city so that the order can be printed later
	int prev[currentSize];
	PriorityQueue<City> pq;

	for (int i = 0; i < currentSize; i++)
	{
		distance[i] = INF;
		visited[i] = 0;
	}
	
	// The distance to the start city is 0, and add it to the queue
	distance[startIndex] = 0;	
	visited[startIndex] = 0;
	City firstCity = *cities.getElement(startIndex);
	firstCity.weight = 0;
	firstCity.from = firstCity.index;
	pq.push(firstCity);

	while (pq.getSize() > 0)
	{
		// We know that popping from the min heap priority queue to get the city with the least distance takes O(log(V)) where V is the number of cities.
		// This operation happens for every city V. So we have O(V*log(V) 
		City currentCity = pq.pop();
		visited[currentCity.index] = 1;

		LinkedList<City>* cityNeighbors = adjacencyList.getElement(currentCity.index);

		/** The runtime of this method is independent of the popping runtime (seen above), so the two runtimes will be added instead of multiplied.   
		*   We know that each city (V) will only be added one time to the queue.
		*   Therefore, the updateNeighborsForShorterPath will end up iterating over every possible edge (E).
		*   Adding an edge takes O(log(V)) time.
		*   Therefore, by checking every edge and pushing each city, we have the runtime O(E*log(V))
		*/
    	cityNeighbors->updateNeighborsForShorterPath(visited, pq, currentCity.index, distance, prev);
	}

	// Find the ending time and call the method to print the results
	auto end = chrono::steady_clock::now();
	double timeTaken = double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000000;
	printDijkstra(prev, distance, startIndex, endIndex, timeTaken);
}

/**
 * Print the cities in the order they were visited along with the distance between cities. Print out the time taken at the end.
 * @param int[] - Prev is an array that contains the index of the city that a city came from. I.E. prev[5] has the index of the city used to get to city 5
 * @param int[] - distances contains the minimum distance to get to each city
 * @param int - startIndex is the index of the start city
 * @param int - endIndex is the index of the end city
 * @param dobule - timeTaken is the amount of time to run the SSSP algorithm
 * O(V) where V is the number of cities in the graph
 */
void Graph::printDijkstra(int prev[], int distances[], int startIndex, int endIndex, double timeTaken)
{
	int lastWeight = 0, numberOfCities = 0, copyEnd = endIndex;

	// Calculate the number of cities used to get to the end city
	// Start at the index of the end city. Use the prev array to keep jumping back until we get to the start cities index.
	while (copyEnd != startIndex)
	{
		copyEnd = prev[copyEnd];
		numberOfCities++;
	}

	copyEnd = endIndex;
	int path[numberOfCities];

	// Prev contains distances to every city. We only want the path to get to the end city
	// Copy the path to get to the end city into the path array
	for (int i = numberOfCities - 1; i >= 0; i--)
	{
		path[i] = copyEnd;
		copyEnd = prev[copyEnd];
	}

	// Use the path and distances arrays to print out directions to get from the start to the end city.
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

Graph::~Graph()
{
	adjacencyList.freeLL();
}