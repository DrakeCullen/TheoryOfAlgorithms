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
	head = new Node();
	tail = new Node();
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
void LinkedList<T>::push(Node* newNode) 
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
	Node* nodeToDelete = head->next;
	T data = nodeToDelete->data;

	head->next = nodeToDelete->next;
	nodeToDelete->next->prev = head;
	delete nodeToDelete;
	size--;
	return data;
}

template<typename T> 
void LinkedList<T>::checkNeighbors(bool visited[], PriorityQueue<Node> &pq)
{
	Node* curr = head->next;

	while (curr != tail) {
		if (!visited[curr->index])
			pq.push(*curr);
		curr = curr->next;
	}
}

template<typename T> 
void LinkedList<T>::checkShortestPath(bool visited[], PriorityQueue<Node> &pq, int index, int distance[], int prev[])
{
	Node* curr = head->next;

	while (curr != tail) {
		if (!visited[curr->index])
		{
			int newDistance = distance[index] + curr->weight;
			if (newDistance < distance[curr->index])
			{
				distance[curr->index] = newDistance;
				prev[curr->index] = index;
				pq.push(*curr);
			}
			
		}
		curr = curr->next;
	}
}

/**
 * Delete the allocated memory from the heap. 
 * O(n) where n is the size of the Linked List
 */
template<typename T> 
void LinkedList<T>::deleteAll() 
{
	Node* curr = head;
	Node* prev;

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
	Node* curr = head->next;
	while(curr != tail) 
	{
		cout<<curr->data<<' '<<curr->weight<<"... ";
		curr = curr->next;
	}
	cout<<endl;
}

template<typename T> 
void LinkedList<T>::printReverse() 
{
	Node* curr = tail->prev;
	while(curr != head) 
	{
		cout<<curr->data<<' ';
		curr = curr->prev;
	}
	cout<<endl;
}
