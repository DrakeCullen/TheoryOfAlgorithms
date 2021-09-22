/**
    CSCI-480 - Assignment 1
    @file City.cpp
    @author Drake Cullen
    City is the basic building block for the project. It acts as a node in linked lists, queues, etc.
*/

#ifndef CITY_H
#define CITY_H

#include <string>

using namespace std;

class City {
public:
	// The name of the city
	string data;
	// Each city has an index assigned to it for easy lookup later
	int index;
	// The cost of traveling to this city
	int weight;
	// From stores an integer value of the city that came before this city
	int from;
	City* next;
	City* prev;
};

#endif
