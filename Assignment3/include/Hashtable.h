/**
    CSCI-480 - Assignment 3
    @file Hashtable.h
    @author Drake Cullen
	The hashtable contains the hash function as well as the array of linked lists to store the words.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include "../src/LinkedList.cpp"

class Hashtable {
	private:
		int wordCount;
		int collisions;
		int hSize;
		LinkedList<Word>* table;

	public:
		Hashtable(int);
		
		int getTotalWordCount();

		void calculateCollisions();

		int getCollisionCount();

		Word* getWord(string&);

		int hash(string&);

		void addWord(string&);

		void createHeap(Heap<Word> &);

		~Hashtable();
};

#endif