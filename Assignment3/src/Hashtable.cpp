

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

void Hashtable::calculateCollisions()
{
	collisions = 0;
	for (int i = 0; i < hSize; i++)
		if (table[i].getSize() > 1)
			collisions++;
}

int Hashtable::getCollisionCount()
{
	return collisions;
}


// The initial and shift value were calculated vy running a simulation with all values from 0-10,000 for initial and 0-9 for shifting

int Hashtable::hash(string &word)
{
	long long hash = 530;
	for (unsigned int i = 0; i < word.length(); i++) 
		hash = ((hash << 8) + word[i]) % hSize;

	return hash % hSize;
}

Word* Hashtable::getWord(string &word)
{
	int index = hash(word);
	Word* result = table[index].getWord(word);
	if (result == nullptr)
		return nullptr;
	return table[index].getWord(word);
}

void Hashtable::addWord(string &word)
{
	int index = hash(word);
	
	// If a new word is added, it returns the number of elements in the linked list.
	int size = table[index].addOrUpdateWord(word);
	if (size != 0)
		wordCount++;
}

void Hashtable::addWordCust(string& word, int start, int shift)
{
	long long hash = start;
	for (unsigned int i = 0; i < word.length(); i++) 
		hash = ((hash << shift) + word[i]) % hSize;
	table[hash].addOrUpdateWord(word);
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