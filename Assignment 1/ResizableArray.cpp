#include "ResizableArray.h"

template<typename T> 
ResizableArray<T>::ResizableArray(int newSize)
{
    maxSize = newSize;
    currentSize = 0;
    array = new T[newSize];
}

template<typename T> 
void ResizableArray<T>::enlargeArray() 
{
    maxSize *= 2;
    T* newArray = new T[maxSize];

    for (int i = 0; i < currentSize; i++)
        newArray[i] = array[i];
    
    
    delete[] array;
    array = newArray;
}

template<typename T> 
void ResizableArray<T>::push(T newItem)
{
    if (currentSize + 1 == maxSize)
        enlargeArray();
    
    array[currentSize++] = newItem;
}

template<typename T> 
T ResizableArray<T>::operator[](T index)
{
    return array[index];
}

template<typename T> 
void ResizableArray<T>::appendNode(int index, Node<T> *newNode)
{
    array[index].push(0,0);
    array[index].print();
    return array[index];
}

template<typename T> 
void ResizableArray<T>::swap(int firstIndex, int secondIndex)
{
    T temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

template<typename T> 
void ResizableArray<T>::moveToTop(int lastEntry)
{
    array[0] = array[lastEntry];
    array[lastEntry] = 100000000;
}

template<typename T> 
ResizableArray<T>::~ResizableArray()
{
    delete[] array;
    array = nullptr;
}
