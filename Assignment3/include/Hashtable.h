

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

		int getCollisionCount();

		Word* getWord(string&);

		int basicHash(string&);

		int betterHash(string&);

		void addWord(string&);

		void createHeap(Heap<Word> &);

		~Hashtable();
};

#endif