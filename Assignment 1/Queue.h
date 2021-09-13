#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename T> class Queue {
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	
	public:
		Queue();
		
		int getSize();	
		
		bool isEmpty();
		
		void push(T value);
		
		T pop();

		void deleteAll();
		
		~Queue();
};


#endif