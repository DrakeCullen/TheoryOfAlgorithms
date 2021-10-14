/**
    CSCI-480 - Assignment 3
    @file LinkedList.h
    @author Drake Cullen
	The linked list is templatized so it can store any type.
*/

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

		T* getWord(string &word);

		bool addOrUpdateWord(string &word);

		void addAllToHeap(Heap<Word> &);

		~LinkedList();
};

#endif