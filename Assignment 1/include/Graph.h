#ifndef GRAPH_H
#define GRAPH_H


#include "AdjacencyList.h"
#include "../src/AdjacencyList.cpp"

#include <fstream>
#include <sstream>

class Graph {
private:
	AdjacencyList<City> adj;
    int currentSize;
    // Make dynamic later
    ResizableArray<City> cities;
    
    void readCities(istream &input, int i, bool &validInput);

	void readDistances(istream &input, int i);
public:
    Graph();
    
	void addEdge(int vertex1, int vertex2, string data, int weight = 0);

    void readInput(string filename);

    int findCityIndex(string city);

    //Should take in file too. Actually main should, we good
    //Take in city name and find index
    void MST(int startIndex = 0);

    //Same as above
    void dijkstra(int startIndex, int endIndex);

    void printMST(City ordering[], double timeTaken);

    void printDijkstra(int prev[], int distances[], int startIndex, int endIndex, double timeTaken);
};

#endif