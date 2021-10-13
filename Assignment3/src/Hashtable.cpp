

#include "../include/Hashtable.h"

/**
 * Default Constructor that allocates memory for the head and tail pointers and links them.
 * O(1)
 */
Hashtable::Hashtable(int size) 
{
	table = new LinkedList<Word>[size];
	wordCount = 0;
	collisions = 0;
	hSize = size;
}

int Hashtable::getTotalWordCount()
{
	return wordCount;
}

int Hashtable::getCollisionCount()
{
	return collisions;
}

int Hashtable::basicHash(string &word)
{
	return word.length() % hSize;
}

// The initial and shift value were calculated vy running a simulation with all values from 0-10,000 for initial and 0-9 for shifting

int Hashtable::betterHash(string &word)
{
	long long hash = 530;
	for (unsigned int i = 0; i < word.length(); i++) 
		hash = ((hash << 8) + word[i]) % hSize;

	return hash % hSize;
}

Word* Hashtable::getWord(string &word)
{
	int index = betterHash(word);
	return table[index].getWord(word);
}

void Hashtable::addWord(string &word)
{
	int index = betterHash(word);
	
	// If a new word is added, it returns the number of elements in the linked list.
	int size = table[index].addOrUpdateWord(word);
	if (size >= 1)
	{
		wordCount++;
		if (size > 1)
			collisions++;
	}
}

void Hashtable::createHeap(Heap<Word> &heap)
{
    for (int i = 0; i < hSize; i++)
		table[i].addAllToHeap(heap);
}


Hashtable::~Hashtable()
{
	delete[] table;
}