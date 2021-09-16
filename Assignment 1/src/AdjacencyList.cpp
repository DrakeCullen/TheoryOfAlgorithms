/**
    CSCI-480 - Assignment 1
    @file AdjacencyList.cpp
    @author Drake Cullen
*/

#include "../include/AdjacencyList.h"

template<typename T> 
AdjacencyList<T>::AdjacencyList(int newSize)
{
    maxSize = newSize;
    currentSize = 0;
    array = new LinkedList<T>[newSize];
}

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

template<typename T> 
void AdjacencyList<T>::addEdge(int index, Node<T> *newNode)
{
    array[index].push(newNode);
}

template<typename T> 
void AdjacencyList<T>::calculateSize(int vertex1, int vertex2)
{
    currentSize = vertex1 > currentSize ? vertex2 : currentSize;
    currentSize = vertex2 > currentSize ? vertex2 : currentSize;
    if (currentSize + 1 == maxSize)
        enlargeArray();
}

template<typename T> 
void AdjacencyList<T>::print()
{
    for (int i = 0; i <= currentSize; i++) 
	{
		cout<<i<<": ";
		array[i].print();
	}
}


template<typename T> 
AdjacencyList<T>::~AdjacencyList()
{
    for (unsigned int i = 0; i < maxSize; i++)
        array[i].deleteAll();
    delete[] array;
    array = nullptr;
}



