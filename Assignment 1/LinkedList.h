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
		
		bool isEmpty();
		
		void push(T value, int pos = 0);
		
		T pop(int pos = 0);
		
		void print();
		
		void printReverse();

         void checkForAllElements(Queue<T> &queue, bool visited[]);
		
		void deleteAll();
		
		~LinkedList();
};

#endif