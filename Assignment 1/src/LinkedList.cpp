/**
    CSCI-480 - Assignment 1
    @file LinkedList.cpp
    @author Drake Cullen
*/

#include "../include/LinkedList.h"

/**
 * Default Constructor that allocates memory for the head and tail pointers and links them.
 * O(1)
 */
template<typename T> 
LinkedList<T>::LinkedList() 
{
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	tail->prev = head;
	size = 0;
}

/**
 * Return the size of the linked list.
 * O(1)
 */
template<typename T> 
int LinkedList<T>::getSize() 
{ 
	return size; 
}

/**
 * Add a new element to the front of a linked list and increase the size variable by one.
 * O(1)
 *
 * @param newNode -> An instance of the node class that is added to the Linked List
 */
template<typename T> 
void LinkedList<T>::push(Node<T>* newNode) 
{
	newNode->next = head->next;
	head->next->prev = newNode;
	newNode->prev = head;
	head->next = newNode;
	size++;
}

/**
 * Delete the top element from the Linked List.
 * O(1)
 */
template<typename T> 
T LinkedList<T>::pop() 
{
	Node<T>* nodeToDelete = head->next;
	T data = nodeToDelete->data;

	head->next = nodeToDelete->next;
	nodeToDelete->next->prev = head;
	delete nodeToDelete;
	size--;
	return data;
}

/**
 * Delete the allocated memory from the heap. 
 * O(n) where n is the size of the Linked List
 */
template<typename T> 
void LinkedList<T>::deleteAll() 
{
	Node<T>* curr = head;
	Node<T>* prev;

	while (prev != tail) {
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	size = 0;
}

//Remove after testing
template<typename T> 
void LinkedList<T>::print() 
{
	Node<T>* curr = head->next;
	while(curr != tail) 
	{
		cout<<curr->data<<' ';
		curr = curr->next;
	}
	cout<<std::endl;
}

template<typename T> 
void LinkedList<T>::printReverse() 
{
	Node<T>* curr = tail->prev;
	while(curr != head) 
	{
		cout<<curr->data<<' ';
		curr = curr->prev;
	}
	cout<<std::endl;
}
