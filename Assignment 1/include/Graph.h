#ifndef GRAPH_H
#define GRAPH_H


#include "AdjacencyList.h"
#include "../src/AdjacencyList.cpp"

#include <fstream>
#include <sstream>

template <typename T> class Graph {
private:
	AdjacencyList<T> adj;
    int currentSize;
    // Make dynamic later
    Node<T> cities[128];
    
    void readCities(istream &input, int i);

	void readDistances(istream &input, int i);
public:
    Graph();

	void addEdge(int vertex1, int vertex2, string data, int weight = 0);

    void readInput(string filename);

    //Should take in file too. Actually main should, we good
    //Take in city name and find index
    void MST(int startIndex = 0);

    //Same as above
    void dijkstra(int startIndex, int endIndex);

    void printMST(Node<T> ordering[]);

    void printDijkstra(int prev[], int distances[], int startIndex, int endIndex);
};

#endif