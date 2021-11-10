/**
    CSCI-480 - Assignment 4
    @file Graph.h
    @author Drake Cullen
	Create a graph using an adjacency list. Can read in data, find the shortest path using a*, and print the shortest path.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

class Graph {
private:
    //The adjacency list is made up of a vector of vectors.
	vector<vector<Node>> adjacencyList;

    void readWeights(string weightFilename);

    void readHeuristics(string weightHeuristics);
    
public:
    void readInput(string weightFilename, string heuristicFilename);

    void aStar(int startIndex, int endIndex);

    void printAStar(double timeTaken, int endIndex, int startIndex, int prev[]);
};

#endif