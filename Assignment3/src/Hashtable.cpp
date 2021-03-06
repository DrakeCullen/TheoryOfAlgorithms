/**
    CSCI-480 - Assignment 3
    @file Hashtable.cpp
    @author Drake Cullen
	The hashtable contains the hash function as well as the array of linked lists to store the words.
*/

#include "../include/Hashtable.h"

/**
 * Default constructor that inititializes the size of the array to the size passed in.
 * @param int -> The size of the array.
 * O(1)
 */
Hashtable::Hashtable(int size) 
{
	table = new LinkedList<Word>[size];
	wordCount = 0;
	collisions = 0;
	hSize = size;
}

/**
 * Return the total number of words.
 * @return int -> The total number of words
 * O(1)
 */
int Hashtable::getTotalWordCount()
{
	return wordCount;
}

/**
 * Loop through each linked list. If there is more than one element in a list, increase the collision count by one.
 * O(n) where n is the number of unique words.
 */
void Hashtable::calculateCollisions()
{
	for (int i = 0; i < hSize; i++)
		if (table[i].getSize() > 1)
			collisions++;
}

/**
 * Return the number of collisions.
 * @param int -> The total number of collisions.
 * O(1)
 */
int Hashtable::getCollisionCount()
{
	return collisions;
}

//
/**
 * Return the hash of a word.
 * The initial and shift value were calculated by running a simulation.
 * The initial hash values were tested from0-10,000 with corresponding
 * bit shifting from 0-25.
 * 530 and 8 turned out to minimize the number of collisions.
 * @param string -> The word you would like to hash
 * @return int -> The hash of the word.
 * O(1)
 */
int Hashtable::hash(string &word)
{
	long long hash = 530;
	for (unsigned int i = 0; i < word.length(); i++) 
		hash = ((hash << 8) + word[i]) % hSize;
	return hash % hSize;
}

/**
 * Lookup and return a word from the hash table.
 * @param string -> The word you would like to search for
 * @param Word* -> A pointer to the location of the word you searched for. Nullptr if the word isn't found.
 * O(1) There should be little to no collisions, so this function should usually execute in constant time.
 */
Word* Hashtable::getWord(string &word)
{
	int index = hash(word);
	Word* result = table[index].getWord(word);
	if (result == nullptr)
		return nullptr;
	return table[index].getWord(word);
}

/**
 * Calculate the hash of a word, than add it to the correct linked list.
 * @param string -> The word you would like to add
 * O(1) The array lookup time is constant, and adding to the linked list should be constant because there are little to no collisions.
 */
void Hashtable::addWord(string &word)
{
	int index = hash(word);
	
	// If a new word is added, it returns the number of elements in the linked list.
	int size = table[index].addOrUpdateWord(word);
	if (size != 0)
		wordCount++;
}

/**
 * Loop through the array containing linked lists, add all the words to the heap.
 * @param string -> The heap that the words will be added to.
 * O(n) Where n is the total number of unique words.
 */
void Hashtable::createHeap(Heap<Word> &heap)
{
    for (int i = 0; i < hSize; i++)
		table[i].addAllToHeap(heap);
}

/**
 * Delete the memory allocated for the dynamic array.
 * O(n) This destructor calls the linked list destructor, so in turn each linked list must be deleted.
 */
Hashtable::~Hashtable()
{
	delete[] table;
}