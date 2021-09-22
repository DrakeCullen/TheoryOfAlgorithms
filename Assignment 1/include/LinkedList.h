/**
    CSCI-480 - Assignment 1
    @file LinkedList.cpp
    @author Drake Cullen
	Linked Lists are used to construct the adjacency matrix. The class can be used for other purposes because it is templatized.
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "City.h"
#include "PriorityQueue.h"
#include "../src/PriorityQueue.cpp"

template <typename T> class LinkedList {
	private:
		City* head;
		City* tail;
		int size;
	
	public:
		LinkedList();
		
		int getSize();
				
		void push(City* newCity);

		T pop();

		void addUnvisitedNeighborsToQueue(bool visited[], PriorityQueue<City> &pq);

		void updateNeighborsForShorterPath(bool visited[], PriorityQueue<City> &pq, int index, int distance[], int prev[]);

		void deleteAll();
};

#endif