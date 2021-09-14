#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "ResizableArray.h"
#include "../src/ResizableArray.cpp"
#include <iostream>

using namespace std;

template <typename T> 
class PriorityQueue 
{
    private:
        ResizableArray<T> dynamicArray;
        int currentIndex = 0;

        void moveUp();

        T getLeftChild(int index);

        T getRightChild(int index);

        void moveDown();

    public:
        void push(T newItem);

        T pop();

        int getSize();

        void print();
};

#endif