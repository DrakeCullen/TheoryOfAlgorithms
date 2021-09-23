/**
    CSCI-480 - Assignment 1
    @file Graph.h
    @author Drake Cullen
	Create a graph using an adjacency list. Can read in data, find MST, and find the single source shortest path,
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"
#include "../src/LinkedList.cpp"
#include "ResizableArray.h"
#include "../src/ResizableArray.cpp"

#include <fstream>
#include <sstream>

class Graph {
private:
    int currentSize;

    //The adjacency list is a resizable array where each element is a linked list
	ResizableArray<LinkedList<City>> adjacencyList;
    // Each index store a city. Useful when looking up information about a city.
    ResizableArray<City> cities;
    
    void readCities(istream &input, int i, bool &validInput);

	void readDistances(istream &input, int i);
public:
    Graph();
    
	void addEdge(int city1, int city2, string name, int weight = 0);

    void readInput(string filename);

    int findCityIndex(string city);

    void MST(int startIndex = 0);

    void dijkstra(int startIndex, int endIndex);

    void printMST(City ordering[], double timeTaken);

    void printDijkstra(int prev[], int distances[], int startIndex, int endIndex, double timeTaken);
};

#endif