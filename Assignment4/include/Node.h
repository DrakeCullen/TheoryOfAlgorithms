/**
    CSCI-480 - Assignment 4
    @file City.h
    @author Drake Cullen
    Node is the basic building block for the project. It stores information abot each point
*/

#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
public:
	// Each node has an index assigned to it
	int index;
	// The cost of traveling to this node
	double weight;
	// From stores an integer value of the node that came before this node
	int from;
	// H is the heuristic value
	double h;
};

#endif
