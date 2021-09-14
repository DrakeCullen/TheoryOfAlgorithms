#include "PriorityQueue.h"

template<typename T> 
void PriorityQueue<T>::moveUp()
{
    int i = currentIndex;
    
    while (dynamicArray[i] < dynamicArray[(i - 1) / 2] && i >= 0) 
    {
        dynamicArray.swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

template<typename T>
T PriorityQueue<T>::getLeftChild(int index)
{
    if (2 * index + 1 < currentIndex)
        return dynamicArray[2 * index + 1];
    else 
        return dynamicArray[index];
}

template<typename T>
T PriorityQueue<T>::getRightChild(int index)
{
    if (2 * index + 1 < currentIndex)
        return dynamicArray[2 * index + 2];
    else 
        return dynamicArray[index];
}

template<typename T>
void PriorityQueue<T>::moveDown()
{
    int index = 0;
    T current, leftChild, rightChild;

    do
    {
        T current = dynamicArray[index];
        T leftChild = getLeftChild(index);
        T rightChild = getRightChild(index);

        if (leftChild <= rightChild && leftChild < current)
        {
            dynamicArray.swap(index, 2 * index + 1);
            index = 2 * index + 1;
        }

        else if (rightChild < current)
        {
            dynamicArray.swap(index, 2 * index + 2);
            index = 2 * index + 2;
        }
    }
    while (index * 2 + 1 < currentIndex && (dynamicArray[index] > getLeftChild(index) || dynamicArray[index] > getRightChild(index)));
}

template<typename T>
void PriorityQueue<T>::push(T newItem)
{
    dynamicArray.push(newItem);
    moveUp();
    currentIndex++;
}

template<typename T>
T PriorityQueue<T>::pop()
{
    T topValue = dynamicArray[0];
    currentIndex--;
    dynamicArray.moveToTop(currentIndex);
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
        cout<<dynamicArray[i]<<' ';
    cout<<endl;
}