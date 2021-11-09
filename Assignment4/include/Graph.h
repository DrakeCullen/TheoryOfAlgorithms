/**
    CSCI-480 - Assignment 1
    @file Graph.h
    @author Drake Cullen
	Create a graph using an adjacency list. Can read in data, find MST, and find the single source shortest path,
*/

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

#include "Node.h"
#include <vector>
#include <queue>

#include <fstream>
#include <sstream>

class Graph {
private:
    int currentSize;

    //The adjacency list is a resizable array where each element is a linked list
	vector<vector<Node>> adjacencyList;

    // Each index stores a city. Useful when looking up information about a city.
    //ResizableArray<City> cities;

    void readWeights(string weightFilename);

    void readHeuristics(string weightHeuristics);
    
public:
    Graph();
    
    void readInput(string weightFilename, string heuristicFilename);

    void aStar(int startIndex, int endIndex);

    void printDijkstra(int prev[], double distances[], int startIndex, int endIndex, double timeTaken);
};

#endif