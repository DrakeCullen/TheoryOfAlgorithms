/**
    CSCI-480 - Assignment 1
    @file PriorityQueue.cpp
    @author Drake Cullen
*/

#include "../include/PriorityQueue.h"

template<typename T> 
PriorityQueue<T>::PriorityQueue(int size)
{
    maxSize = size;
    array = new T[size];
}

template<typename T> 
void PriorityQueue<T>::moveUp()
{
    int i = currentIndex;
    
    while (array[i] < array[(i - 1) / 2] && i >= 0) 
    {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

template<typename T>
T PriorityQueue<T>::getLeftChild(int index)
{
    if (2 * index + 1 < currentIndex)
        return array[2 * index + 1];
    else 
        return array[index];
}

template<typename T>
T PriorityQueue<T>::getRightChild(int index)
{
    if (2 * index + 1 < currentIndex)
        return array[2 * index + 2];
    else 
        return array[index];
}

template<typename T>
void PriorityQueue<T>::swap(int firstIndex, int secondIndex)
{
    T temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

template<typename T>
void PriorityQueue<T>::moveDown()
{
    int index = 0;
    T current, leftChild, rightChild;

    do
    {
        current = array[index];
        leftChild = getLeftChild(index);
        rightChild = getRightChild(index);

        if (leftChild <= rightChild && leftChild < current)
        {
            swap(index, 2 * index + 1);
            index = 2 * index + 1;
        }

        else if (rightChild < current)
        {
            swap(index, 2 * index + 2);
            index = 2 * index + 2;
        }
    }
    while (index * 2 + 1 < currentIndex && (array[index] > getLeftChild(index) || array[index] > getRightChild(index)));
}

template<typename T> 
void PriorityQueue<T>::enlargeArray() 
{
    maxSize *= 2;
    T* newArray = new T[maxSize];
    for (int i = 0; i <= currentIndex; i++)
        newArray[i] = array[i];

    delete[] array;
    array = newArray;
}

template<typename T>
void PriorityQueue<T>::push(T newItem)
{
    if (currentIndex + 1 >= maxSize)
        enlargeArray();
    array[currentIndex] = newItem;
    moveUp();
    currentIndex++;
}

template<typename T>
T PriorityQueue<T>::pop()
{
    T topValue = array[0];
    currentIndex--;
    array[0] = array[currentIndex];
    moveDown();
    return topValue;
}

template<typename T>
int PriorityQueue<T>::getSize()
{
    return currentIndex;
}

template<typename T>
void PriorityQueue<T>::print()
{
    for (int i = 0; i < currentIndex; i++)
        cout<<array[i]<<' ';
    cout<<endl;
}

template<typename T> 
PriorityQueue<T>::~PriorityQueue()
{
    delete[] array;
}