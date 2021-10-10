

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


Word* Hashtable::getWord(string &word)
{
	int index = basicHash(word);
	return table[index].getWord(word);
}

void Hashtable::addWord(string &word)
{
	int index = basicHash(word);
	
	// If a new word is added, it returns the number of elements in the linked list.
	int size = table[index].addOrUpdateWord(word);
	if (size >= 1)
	{
		wordCount++;
		if (size > 1)
			collisions++;
	}

}

Hashtable::~Hashtable()
{
	delete[] table;
}