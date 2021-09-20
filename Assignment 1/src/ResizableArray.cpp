/**
    CSCI-480 - Assignment 1
    @file ResizableArray.cpp
    @author Drake Cullen
*/

#include "../include/ResizableArray.h"

/**
 * Default Constructor that allocates memory for an array of type T. Default size is 2.
 * Each element in an array holds a linked list.
 * O(1)
 * * @param newSize -> The original size of the array
 */
template<typename T> 
ResizableArray<T>::ResizableArray(int newSize)
{
    maxSize = newSize;
    currentSize = 0;
    array = new T[newSize];
}


/**
 * If the array becomes full, we must allocate new space on the heap and delete the old array.
 * This is inspired by the way vectors work in c++. Everytime we make a new array, the size is doubled.
 * O(n). Iterate over and copy every element.
 */
template<typename T> 
void ResizableArray<T>::enlargeArray() 
{
    maxSize *= 2;
    T* newArray = new T[maxSize];
    for (int i = 0; i <= currentSize; i++)
        newArray[i] = array[i];
    
    delete[] array;
    array = newArray;
}

template<typename T> 
T* ResizableArray<T>::getElement(int index)
{
    return &array[index];
}

template<typename T> 
void ResizableArray<T>::calculateSize()
{
    if (currentSize + 1 == maxSize)
        enlargeArray();
    currentSize++;
}

template<typename T> 
void ResizableArray<T>::insert(int index, T newItem)
{
    calculateSize();
    array[currentSize-1] = newItem;
}

template<typename T> 
T ResizableArray<T>::pop()
{
    T topItem = array[0];
    currentSize--;
    array[0] = array[currentSize];
    return topItem;
}

/**
 * Swap two nodes in the array.
 * O(1). Indexes can be accessed in constant time. 
 * @param firstIndex -> The index of the first node
 * @param secondIndex -> The index of the second node
 */
template<typename T> 
void ResizableArray<T>::swap(int firstIndex, int secondIndex)
{
    T temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

/**
 * Go through and delete every linked list and the dynamic array.
 * O(n+m). Where n is the number of edges and m is the number of vertices
 */
template<typename T> 
ResizableArray<T>::~ResizableArray()
{
    //for (unsigned int i = 0; i < maxSize; i++)
    //    array[i].deleteAll();
    delete[] array;
    array = nullptr;
}



