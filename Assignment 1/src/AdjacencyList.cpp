/**
    CSCI-480 - Assignment 1
    @file AdjacencyList.cpp
    @author Drake Cullen
*/

#include "../include/AdjacencyList.h"

/**
 * Default Constructor that allocates memory for an array of type T. Default size is 2.
 * Each element in an array holds a linked list.
 * O(1)
 * * @param newSize -> The original size of the array
 */
template<typename T> 
AdjacencyList<T>::AdjacencyList(int newSize)
{
    maxSize = newSize;
    currentSize = 0;
    array = new LinkedList<T>[newSize];
}

/**
 * If the array becomes full, we must allocate new space on the heap and delete the old array.
 * This is inspired by the way vectors work in c++. Everytime we make a new array, the size is doubled.
 * O(n). Iterate over and copy every element.
 */
template<typename T> 
void AdjacencyList<T>::enlargeArray() 
{
    maxSize *= 2;
    LinkedList<T>* newArray = new LinkedList<T>[maxSize];
    for (int i = 0; i <= currentSize; i++)
        newArray[i] = array[i];
    
    delete[] array;
    array = newArray;
}

/**
 * Add a new edge to the adjacency list. 
 * Go to the corresponding linked list and push the node on.
 * O(1). Accessing the index is O(1), and pushing to the front of a linked list is O(1)
 * * @param index -> The index of the graph that you are coming from
 * * @param newNode -> A pointer to the node that you would like to add
 */
template<typename T> 
void AdjacencyList<T>::addEdge(T index, Node<T> *newNode)
{
    array[index].push(newNode);
}


// This isn't needed?
template<typename T> 
void AdjacencyList<T>::calculateSize(int vertex1, int vertex2)
{
    currentSize = vertex1 > currentSize ? vertex2 : currentSize;
    currentSize = vertex2 > currentSize ? vertex2 : currentSize;
    if (currentSize + 1 == maxSize)
        enlargeArray();
}

// Remove after testing
template<typename T> 
void AdjacencyList<T>::print()
{
    for (int i = 0; i <= currentSize; i++) 
	{
		cout<<i<<": ";
		array[i].print();
	}
}

/**
 * Go through and delete every linked list and the dynamic array.
 * O(n+m). Where n is the number of edges and m is the number of vertices
 */
template<typename T> 
AdjacencyList<T>::~AdjacencyList()
{
    for (unsigned int i = 0; i < maxSize; i++)
        array[i].deleteAll();
    delete[] array;
    array = nullptr;
}



