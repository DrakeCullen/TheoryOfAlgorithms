#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

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
		
		void deleteAll();

		//Remove after testing
		void print();
		
		void printReverse();
};

#endif