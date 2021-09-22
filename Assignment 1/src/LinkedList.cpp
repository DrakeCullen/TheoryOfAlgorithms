/**
    CSCI-480 - Assignment 1
    @file LinkedList.cpp
    @author Drake Cullen
	Linked Lists are used to construct the adjacency matrix. The class can be used for other purposes because it is templatized.
*/

#include "../include/LinkedList.h"

/**
 * Default Constructor that allocates memory for the head and tail pointers and links them.
 * O(1)
 */
template<typename T> 
LinkedList<T>::LinkedList() 
{
	head = new City();
	tail = new City();
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
void LinkedList<T>::push(City* newCity) 
{
	newCity->next = head->next;
	head->next->prev = newCity;
	newCity->prev = head;
	head->next = newCity;
	size++;
}

/**
 * Delete the top element from the Linked List. Decrease the size by one
 * @return T - return the data from the top element of the list
 * O(1)
 */
template<typename T> 
T LinkedList<T>::pop() 
{
	City* CityToDelete = head->next;
	T data = CityToDelete->data;

	head->next = CityToDelete->next;
	CityToDelete->next->prev = head;
	delete CityToDelete;
	size--;
	return data;
}

/**
 * Utilized in finding the MST
 * Go through all the cities that this city is connected to. Add them to the priority queue if they havent been visited.
 * @param bool - An array of boolean values representing cities that have been visited. 1 means visited
 * @param PriorityQueue<City> - The priority queue containing the cities that will be explored next
 * O(n) where n is the number of cities connected to the city in question
 */
template<typename T> 
void LinkedList<T>::addUnvisitedNeighborsToQueue(bool visited[], PriorityQueue<City> &pq)
{
	City* curr = head->next;

	while (curr != tail) {
		if (!visited[curr->index])
			pq.push(*curr);
		curr = curr->next;
	}
}

/**
 * Utilized in finding the shortest path
 * Go through all the cities that this city is connected to. If an adjacent city hasn't been visited, then go inside the if statement.
 * If the distance to get to the adjacent city is less by using the city passed as an argument, 
 * then update the adjacent cities distance and add the adjacent city to the priority queue. Update prev so we know how we got to the adjacent city.
 * @param bool - An array of boolean values representing cities that have been visited. 1 means visited
 * @param PriorityQueue<City> - The priority queue containing the cities that will be explored next
 * @param int - The index of the city that is being passed. Used to find values in distance array and prev array
 * @param int - An array of integers containing the shortest distance to reach a city
 * @param int - An array of integers that keeps track of the city used to reach the current city
 * O(n) where n is the number of cities connected to the city in question
 */
template<typename T> 
void LinkedList<T>::updateNeighborsForShorterPath(bool visited[], PriorityQueue<City> &pq, int index, int distance[], int prev[])
{
	City* curr = head->next;

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
	City* curr = head;
	City* prev;

	while (prev != tail) {
		prev = curr;
		curr = curr->next;
		delete prev;
	}

	delete tail;
	size = 0;
}
