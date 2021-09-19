#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include "PriorityQueue.h"
#include "../src/PriorityQueue.cpp"

using namespace std;

template <typename T> class LinkedList {
private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	
	public:
		LinkedList();
		
		int getSize();
				
		void push(Node<T>* newNode);

		T pop();

		void checkNeighbors(bool visited[], PriorityQueue<Node<T>> &pq);

		void checkShortestPath(bool visited[], PriorityQueue<Node<T>> &pq, int index, int distance[], int prev[]);

		
		void deleteAll();

		//Remove after testing
		void print();
		
		void printReverse();
};

#endif