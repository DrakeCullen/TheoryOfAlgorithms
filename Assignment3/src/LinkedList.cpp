

#include "../include/LinkedList.h"

/**
 * Default Constructor that allocates memory for the head and tail pointers and links them.
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
 * Add a new element to the front of a linked list and increase the size variable by one.
 * @param newCity -> An instance of the City class that is added to the Linked List
 * O(1)
 */
template<typename T> 
void LinkedList<T>::push(string &word) 
{
	T* newNode = new T;
	newNode->data = word;
	newNode->count = 1;

	newNode->next = head->next;
	head->next->prev = newNode;
	newNode->prev = head;
	head->next = newNode;
	size++;
}

template<typename T> 
Word* LinkedList<T>::getWord(string &word)
{
	T* temp = head->next;
	while (head != tail)
	{
		if (temp->data == word)
			return temp;
		temp = temp->next;
	}
	return nullptr;
}

template<typename T> 
int LinkedList<T>::addOrUpdateWord(string &word)
{
	T* temp = head->next;
	int size = 1;

	while (temp != tail)
	{
		if (temp->data == word)
		{	
			temp->count++;
			return 0;
		}
		temp = temp->next;
		size++;
	}
	push(word);
	return size;
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
