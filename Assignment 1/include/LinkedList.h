#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include "PriorityQueue.h"
#include "../src/PriorityQueue.cpp"

using namespace std;

template <typename T> class LinkedList {
private:
		Node* head;
		Node* tail;
		int size;
	
	public:
		LinkedList();
		
		int getSize();
				
		void push(Node* newNode);

		T pop();

		void checkNeighbors(bool visited[], PriorityQueue<Node> &pq);

		void checkShortestPath(bool visited[], PriorityQueue<Node> &pq, int index, int distance[], int prev[]);

		
		void deleteAll();

		//Remove after testing
		void print();
		
		void printReverse();
};

#endif