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

void Graph::readWeights(string weightFilename)
{
	ifstream input(weightFilename);
	string line, weight;
	int i = 0;
	while(getline(input, line)) 
	{
		stringstream ss(line);
		vector<Node> connectedCities;
		while(ss >> weight)
		{
			Node newNode;
			newNode.weight = stod(weight);
			connectedCities.push_back(newNode);
		}
		adjacencyList.push_back(connectedCities);
		i++;
	}
	input.close();
}


void Graph::readHeuristics(string weightHeuristics)
{
	ifstream input(weightHeuristics);
	string line, heuristic;
	int i = 0, j = 0;
	while(getline(input, line)) 
	{
		j = 0;
		stringstream ss(line);
		while(ss >> heuristic)
		{
			adjacencyList[i][j].h = stod(heuristic);
			adjacencyList[i][j].index = j;
			adjacencyList[i][j++].from = i;
		}
		i++;
	}
	input.close();
}


/**
 * Handles reading in the input. Calls readCities and readDistances.
 * @param string - The name of the file you would like to read
*/ 
void Graph::readInput(string weightFilename, string heuristicFilename)
{
	readWeights(weightFilename);
	readHeuristics(heuristicFilename);
}


bool operator<(const Node& firstNode, const Node& secondNode) 
{
	return (firstNode.weight + firstNode.h) > (secondNode.weight + secondNode.h);
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
void Graph::aStar(int startIndex, int endIndex)
{
	// Used to measure the time it takes to run the algorithm
	auto start = chrono::steady_clock::now();
	// Represent infinity with the maximum value and integer can store
	const int INF = 2147483646;
	// Arrays to keep track of the shortest distance to a city and whether the city has been visited
	double cost[adjacencyList.size()], actualDistance[adjacencyList.size()];
	bool visited[adjacencyList.size()];
	// Keep track of how we got to a city so that the order can be printed later
	int prev[adjacencyList.size()];
	priority_queue<Node> pq;

	for (unsigned int i = 0; i < adjacencyList.size(); i++)
	{
		cost[i] = INF;
		actualDistance[i] = 0;
		visited[i] = 0;
	}


	Node currentNode;
	// The distance to the start city is 0, and add it to the queue
	cost[startIndex] = 0;	
	visited[startIndex] = 0;
	Node firstNode;
	firstNode.weight = firstNode.h = 0;
	firstNode.index = startIndex;
	firstNode.from = firstNode.index;
	pq.push(firstNode);

	while (pq.size() > 0)
	{
		// We know that popping from the min heap priority queue to get the city with the least distance takes O(log(V)) where V is the number of cities.
		// This operation happens for every city V. So we have O(V*log(V) 
		currentNode = pq.top();
		pq.pop();
		cout<<currentNode.from<<' '<<currentNode.index<<' '<<currentNode.weight<<' '<<currentNode.h<<endl;
		visited[currentNode.index] = 1;

		if (currentNode.index == endIndex) break;

		for (Node nextNode : adjacencyList[currentNode.index])
		{
			if (!visited[nextNode.index] && nextNode.weight != 0)
			{
				double newCost = cost[currentNode.index] + nextNode.weight;
				if (newCost < cost[nextNode.index])
				{
					cost[nextNode.index] = newCost;
					prev[nextNode.index] = currentNode.index;
					nextNode.h = adjacencyList[endIndex][nextNode.index].h;
					pq.push(nextNode);
				}
			}
		}
	}
	cout<<cost[currentNode.index];

	// Find the ending time and call the method to print the results
	auto end = chrono::steady_clock::now();
	double timeTaken = double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000000;
	printDijkstra(prev, actualDistance, startIndex, endIndex, timeTaken);
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
void Graph::printDijkstra(int prev[], double distances[], int startIndex, int endIndex, double timeTaken)
{
	//cout<<"From " << t.from << " to "<< t.index << " with a weight " << t.weight << " and h " << t.h << " total " <<t.weight + t.h << endl;
	/*double lastWeight = 0;
	int numberOfCities = 0, copyEnd = endIndex;

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
	cout << "1: "<< startIndex << " to " << path[0] << " \"distance = " << distances[path[0]] << "\"" << endl;
	lastWeight = distances[path[0]];
	for (int i = 0; i < numberOfCities - 1; i++)
	{
		cout << i + 2 << ": "<< cities.getElement(path[i])->data << " to " << cities.getElement(path[i+1])->data << " \"distance = " << distances[path[i+1]] - lastWeight << "\"" << endl;
		lastWeight = distances[path[i+1]];
	}
	cout<<"Total distance: "<<distances[endIndex]<<endl;
	cout << "\nTime taken to find the shortest path: " << timeTaken << " seconds. \n";*/
	
}