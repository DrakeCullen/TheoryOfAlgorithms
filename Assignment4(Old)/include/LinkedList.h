/**
    CSCI-480 - Assignment 1
    @file LinkedList.h
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
		T* head;
		T* tail;
		int size;
	
	public:
		LinkedList();
		
		int getSize();
				
		void push(T* newCity);

		T pop();

		void addUnvisitedNeighborsToQueue(bool visited[], PriorityQueue<T> &pq);

		void updateNeighborsForShorterPath(bool visited[], PriorityQueue<T> &pq, int index, int distance[], int actualDistance[], int prev[]);

		int getHeuristic(string &destinationCity);

		void print();

		void deleteAll();
};

#endif