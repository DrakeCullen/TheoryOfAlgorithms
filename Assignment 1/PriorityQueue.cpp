#include "PriorityQueue.h"

template<typename T> 
PriorityQueue<T>::PriorityQueue(int size)
{
    array = new T[size];
}

template<typename T> 
void PriorityQueue<T>::moveUp()
{
    int i = currentIndex;
    
    while (array[i] < array[(i - 1) / 2] && i >= 0) 
    {
        array.swap(i, (i - 1) / 2);
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
void PriorityQueue<T>::moveDown()
{
    int index = 0;
    T current, leftChild, rightChild;

    do
    {
        T current = array[index];
        T leftChild = getLeftChild(index);
        T rightChild = getRightChild(index);

        if (leftChild <= rightChild && leftChild < current)
        {
            array.swap(index, 2 * index + 1);
            index = 2 * index + 1;
        }

        else if (rightChild < current)
        {
            array.swap(index, 2 * index + 2);
            index = 2 * index + 2;
        }
    }
    while (index * 2 + 1 < currentIndex && (array[index] > getLeftChild(index) || array[index] > getRightChild(index)));
}

template<typename T>
void PriorityQueue<T>::push(T newItem)
{
    array.push(newItem);
    moveUp();
    currentIndex++;
}

template<typename T>
T PriorityQueue<T>::pop()
{
    T topValue = array[0];
    currentIndex--;
    array.moveToTop(currentIndex);
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