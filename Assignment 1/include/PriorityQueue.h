/**
    CSCI-480 - Assignment 1
    @file PriorityQueue.ch
    @author Drake Cullen
    Priority queue implemented using a min heap
*/

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "ResizableArray.h"

using namespace std;

template <typename T> 
class PriorityQueue 
{
    private:
        ResizableArray<T> array;
        int currentIndex = 0;

        void moveUp();

        void moveDown();

        int getLeftChild(int index);

        int getRightChild(int index);

    public:
        void push(T newItem);

        T pop();

        int getSize();

        ~PriorityQueue();
};

#endif