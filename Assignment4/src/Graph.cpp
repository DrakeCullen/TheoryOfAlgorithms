/**
    CSCI-480 - Assignment 4
    @file Graph.cpp
    @author Drake Cullen
	Create a graph using an adjacency list. Can read in data, find the shortest path using a*, and print the shortest path.
*/

#include "../include/Graph.h"
#include <chrono>


/**
 * Read in the graphs weights and store them in the adjacency list.
 * @param string - The name of the input file
 * O(E) where E is the number of edges in the input file
 */ 
void Graph::readWeights(string weightFilename)
{
	ifstream input(weightFilename);
	string line, weight;

	while(getline(input, line)) 
	{
		stringstream ss(line);
		vector<Node> connectedCities;

		// Extract each weight and add it to the list of connected edges
		while(ss >> weight)
		{
			Node newNode;
			newNode.weight = stod(weight);
			connectedCities.push_back(newNode);
		}
		adjacencyList.push_back(connectedCities);
	}
	input.close();
}

/**
 * Read in the graphs heuristics and store them in the adjacency list.
 * @param string - The name of the input file
 * O(V^2) because every node is connected by a heuristic value, so each input must be read in.
 */ 
void Graph::readHeuristics(string weightHeuristics)
{
	ifstream input(weightHeuristics);
	string line, heuristic;
	int i = 0, j
	;
	while(getline(input, line)) 
	{
		j = 0;
		stringstream ss(line);

		// Extract each heuristic. Stores the heuristic, the nodes index, and which node it came from.
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
 * Handles reading in the input. Calls readWeights and readHeuristics.
 * @param string - The name of the file with the weights
 * @param string - The name of the file with the heuristics
 * O(V^2) Look at the readHeuristics function to find why this is the runtime.
*/ 
void Graph::readInput(string weightFilename, string heuristicFilename)
{
	readWeights(weightFilename);
	readHeuristics(heuristicFilename);
}


/**
 * Overload the < operator. Used to set the ordering for the priority queue
 * @param Node - The first node to compare
 * @param Node - The second node to compare
 * @return bool - Return true if the second node is a better candidate
*/ 
bool operator<(const Node& firstNode, const Node& secondNode) 
{
	return  firstNode.h >  secondNode.h;
}

/**
 * Given a starting and ending node, find the shortest path between them.
 * Add the start node to the priority queue. Initialize all distances to INF except for the starting node.
 * While the priority queue still has nodes and the last city hasn't been reached, check their neighbors to 
 * see they have a potentially better path based on their heuristic.
 * If so, add these cities to the queue and update their distances.
 * @param int - The index of the start node
 * @param int - The index of the end node
 * O((V*log(V)) + E*log(V)) where E is the number of edges and V is the number of cities. Simplifying gives 
 * O(log(V)*(E+V))
 */ 
void Graph::aStar(int startIndex, int endIndex)
{
	// Used to measure the time it takes to run the algorithm
	auto start = chrono::steady_clock::now();
	// Represent infinity with the maximum value and integer can store
	const int INF = 2147483646;
	// Arrays to keep track of the shortest distance to a node and whether the node has been visited
	double cost[adjacencyList.size()];
	bool visited[adjacencyList.size()];
	// Keep track of how we got to a city so that the order can be printed later
	int prev[adjacencyList.size()];
	priority_queue<Node> pq;

	for (unsigned int i = 0; i < adjacencyList.size(); i++)
	{
		cost[i] = INF;
		visited[i] = 0;
	}

	Node firstNode, currentNode;
	cost[startIndex] = firstNode.weight = firstNode.h = 0;	
	firstNode.index = startIndex;
	firstNode.from = firstNode.index;
	pq.push(firstNode);

	while (pq.size() > 0)
	{
		// We know that popping from the min heap priority queue to get the node with the the best potential takes O(log(V)) where V is the number of nodes.
		// In the worst case, this operation happens for every node V. So we have O(V*log(V) 
		currentNode = pq.top();
		pq.pop();
		visited[currentNode.index] = 1;

		if (currentNode.index == endIndex) break;

		// For every connected node
		for (Node nextNode : adjacencyList[currentNode.index])
		{
			// If the node hasn't been visited
			if (!visited[nextNode.index] && nextNode.weight != 0)
			{
				// If the cost is better than what we had
				double newCost = cost[currentNode.index] + nextNode.weight;
				if (newCost < cost[nextNode.index])
				{
					cost[nextNode.index] = newCost;
					prev[nextNode.index] = currentNode.index;
					nextNode.h = adjacencyList[endIndex][nextNode.index].h + newCost;
					pq.push(nextNode);
				}
			}
		}
	}

	// Find the ending time and call the method to print the results
	auto end = chrono::steady_clock::now();
	double timeTaken = double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000000;
	printAStar(timeTaken, endIndex, startIndex, prev);
}


/**
 * Given a starting and ending node, find the shortest path between them.
 * Add the start node to the priority queue. Initialize all distances to INF except for the starting node.
 * While the priority queue still has nodes and the last city hasn't been reached, check their neighbors to 
 * see they have a potentially better path based on their heuristic.
 * If so, add these cities to the queue and update their distances.
 * @param double - The time to run the a* method
 * @param int - The index of the destination node
 * @param int - The index of the start node
 * @param int[] - An array that keeps track of the node that the current node came from
 */ 
void Graph::printAStar(double timeTaken, int endIndex, int startIndex, int prev[])
{	

	int prevIndex = endIndex, totalCost = 0;
	vector<int> path;

	// Recreate the path in the correct order
	while (prevIndex != startIndex)
	{
		path.insert(path.begin(), prevIndex);
		prevIndex = prev[prevIndex];
	}
	path.insert(path.begin(), startIndex);

	// Use the path and distances arrays to print out directions to get from the start to the end node.
	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		cerr << i + 1 << ": "<< path[i] << " to " << path[i+1] << " \"distance = " << adjacencyList[path[i]][path[i+1]].weight << "\"" << " using a heuristic of " << adjacencyList[path[i+1]][endIndex].h << " to the destination."<< endl;
		totalCost += adjacencyList[path[i]][path[i+1]].weight;
	}
	cout<<"Total distance: "<<totalCost<<endl;
	cout << "\nTime taken to find the shortest path: " << timeTaken << " seconds. \n";
	
}