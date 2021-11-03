/**
    CSCI-480 - Assignment 1
    @file LinkedList.cpp
    @author Drake Cullen
	Acts like an array in c++ with O(1) lookup time, but it is resized when it becomes full
*/


#include "../include/ResizableArray.h"

/**
 * Default Constructor that allocates memory for an array of type T. Default size is 128.
 * Each element in an array holds a linked list.
 * O(1)
 * * @param int -> The original size of the array
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

/**
 * Used to access a specific index in the array.
 * * @param int -> The index you would like to access
 * * @return T* - returns a pointer to the item at that position in the array
 *  O(1)
 */
template<typename T> 
T* ResizableArray<T>::getElement(int index)
{
    return &array[index];
}

/**
 * This method makes sure that there is always enough room in the array. It is called everytime an element is added.
 * If the array becomes full, it call the enlargeArray method.
 * O(n) in the worst case when enlargeArray is called. On average, O(1)
 */
template<typename T> 
void ResizableArray<T>::calculateSize()
{
    if (currentSize + 1 == maxSize)
        enlargeArray();
    currentSize++;
}

/**
 * Insert a new item at the end of the array
 * Call the calculateSize method to make sure that there is room before adding the item
 * O(n) in the worst case when enlargeArray is called. Average case of O(1).
 * @param T - The new item that will be added to the array
 */
template<typename T> 
void ResizableArray<T>::insert(T newItem)
{
    calculateSize();
    array[currentSize-1] = newItem;
}

/**
 * Remove the first element in the array. Called from the PriorityQueue class
 * The last element is moved to the fist position. Decrease size by one.
 * O(1)
 * @return T - the element at the front of the
 */
template<typename T> 
T ResizableArray<T>::pop()
{
    T topItem = array[0];
    currentSize--;
    array[0] = array[currentSize];
    return topItem;
}

/**
 * Swap two Citys in the array.
 * O(1). Indexes can be accessed in constant time. 
 * @param firstIndex -> The index of the first City
 * @param secondIndex -> The index of the second City
 */
template<typename T> 
void ResizableArray<T>::swap(int firstIndex, int secondIndex)
{
    T temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

template<typename T> 
void ResizableArray<T>::freeLL()
{
    for (int i = 0; i < maxSize; i++)
        array[i].deleteAll();
}

/**
 * Go through and delete every linked list and the dynamic array.
 * O(V+E). Where V is the number of cities and E is the number of edges. For each city,
 * all the connected cities will be deleted in the linked list. The array will than be deleted.
 */
template<typename T> 
ResizableArray<T>::~ResizableArray()
{
    delete[] array;
    array = nullptr;
}



