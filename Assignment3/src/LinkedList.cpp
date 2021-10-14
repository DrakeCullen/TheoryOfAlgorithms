/**
    CSCI-480 - Assignment 3
    @file LinkedList.cpp
    @author Drake Cullen
	The linked list is templatized so it can store any type.
*/

#include "../include/LinkedList.h"

/**
 * Default Constructor that allocates memory for the head and tail pointers and links them.
 * Sets the size of the linked list to 0.
 * O(1)
 */
template<typename T> 
LinkedList<T>::LinkedList() 
{
	head = new T();
	tail = new T();
	head->next = tail;
	tail->prev = head;
	size = 0;
}

/**
 * Return the size of the linked list.
 * @return int - the size of the linked list
 * O(1)
 */
template<typename T> 
int LinkedList<T>::getSize() 
{ 
	return size; 
}

/**
 * Add a new element to the linked list in alphabetical order and increase the size variable by one.
 * @param string -> The word you would like to add
 * O(1) There should be little to no collisions, so this function should usually execute in constant time.
 */
template<typename T> 
void LinkedList<T>::push(string &word) 
{
	T* newNode = new T;
	newNode->data = word;
	newNode->count = 1;

	T* prev = head;
	T* curr = head->next;

	while (curr != tail && newNode->data < curr->data)
	{
		prev = curr;
		curr = curr->next;
	}

	newNode->next = curr;
	prev->next = newNode;
	newNode->prev = prev;
	curr->prev = newNode;
	size++;
}

/**
 * Check the linked list for a certain word and return a pointer to it.
 * @param string -> The word you would like to search for
 * @return T* -> A pointer to the address of the word, or nullptr if the word doesn't exist in the list.
 * O(1) There should be little to no collisions, so this function should usually execute in constant time.
 */
template<typename T> 
T* LinkedList<T>::getWord(string &word)
{
	T* temp = head->next;

	while (temp != tail)
	{
		if (temp->data == word)
			return temp;
		temp = temp->next;
	}
	return nullptr;
}

/**
 * Search the linked list for a word. If it exists, increase the count by one. If it doesn't exist, add it with the push command.
 * @param string -> The word you would like to add
 * @return bool -> Return 0 if the word is already in the list. Return 1 if the word is new.
 * O(1) There should be little to no collisions, so this function should usually execute in constant time. Push also executes in constant time.
 */
template<typename T> 
bool LinkedList<T>::addOrUpdateWord(string &word)
{
	T* temp = head->next;

	while (temp != tail)
	{
		if (temp->data == word)
		{	
			temp->count++;
			return 0;
		}
		temp = temp->next;
	}
	push(word);
	return 1;
}

template<typename T> 
void LinkedList<T>::addAllToHeap(Heap<Word> &heap)
{
	T* temp = head->next;
	while (temp != tail) {
		heap.push(temp);
		temp = temp->next;
	}
}

/**
 * Delete the allocated memory from the heap. 
 * O(n) where n is the size of the Linked List
 */
template<typename T> 
LinkedList<T>::~LinkedList() 
{
	T* curr = head;
	T* prev;

	while (curr != tail) {
		prev = curr;
		curr = curr->next;
		delete prev;
	}

	delete tail;
	size = 0;
}
