#ifndef RESIZABLEARRAY_H
#define RESIZABLEARRAY_H

#include "LinkedList.h"
#include "LinkedList.cpp"

template <typename T>
class ResizableArray
{
    private:
        int maxSize;
        int currentSize;
        T* array;

        void enlargeArray();

    public:
        ResizableArray(int newSize = 128);

        void push(T newItem);

        T operator[](T index);

        void appendNode(int index, Node<T> *newNode);

        void swap(int firstIndex, int secondIndex);

        void moveToTop(int lastEntry);

        ~ResizableArray();
};

#endif