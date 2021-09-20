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
AdjacencyList<T>::AdjacencyList()
{
}


/**
 * Add a new edge to the adjacency list. 
 * Go to the corresponding linked list and push the node on.
 * O(1). Accessing the index is O(1), and pushing to the front of a linked list is O(1)
 * * @param index -> The index of the graph that you are coming from
 * * @param newNode -> A pointer to the node that you would like to add
 */
template<typename T> 
void AdjacencyList<T>::addEdge(int index, Node *newNode)
{
    array.calculateSize();
    LinkedList<T>* temp = array.getElement(index);
    temp->push(newNode);
}


template<typename T> 
void AdjacencyList<T>::checkNeighbors(bool visited[], PriorityQueue<Node> &pq, int index)
{
    LinkedList<T>* temp = array.getElement(index);
    temp->checkNeighbors(visited, pq);
}

template<typename T> 
void AdjacencyList<T>::checkShortestPath(bool visited[], PriorityQueue<Node> &pq, int index, int distance[], int prev[])
{
    LinkedList<T>* temp = array.getElement(index);
    temp->checkShortestPath(visited, pq, index, distance, prev);
}

template<typename T> 
AdjacencyList<T>::~AdjacencyList()
{
}



