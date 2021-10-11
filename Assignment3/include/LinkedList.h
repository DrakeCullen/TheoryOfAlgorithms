

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../include/Word.h"
#include "Heap.h"
#include "../src/Heap.cpp"

template <typename T> class LinkedList {
	private:
		T* head;
		T* tail;
		int size;
	
	public:
		LinkedList();
		
		int getSize();
				
		void push(string &newNode);

		Word* getWord(string &word);

		int addOrUpdateWord(string &word);

		void addAllToHeap(Heap<Word> &);

		~LinkedList();
};

#endif