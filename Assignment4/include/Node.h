/**
    CSCI-480 - Assignment 1
    @file City.h
    @author Drake Cullen
    City is the basic building block for the project. It acts as a node in linked lists, queues, etc.
*/

#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

using namespace std;

class Node {
public:
	// Each node has an index assigned to it
	int index;
	// The cost of traveling to this node
	double weight;
	// From stores an integer value of the city that came before this city
	int from;
	// H is the heuristic value
	double h;
};

#endif
