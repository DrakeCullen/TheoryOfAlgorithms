/**
    CSCI-480 - Assignment 3
    @file Heap.h
    @author Drake Cullen
	The heap can be a min or max heap depending on what is passed to the constructor.
*/

#ifndef HEAP_H
#define HEAP_H

#include "Word.h"

using namespace std;

template <typename T> 
class Heap 
{
    private:
        Word** heapArr;
        int currentIndex;
        bool maxHeap;

        void moveUp();

        void moveDown();

        int getLeftChild(int index);

        int getRightChild(int index);

        void swap(int, int);

    public:
        Heap(int, bool);

        void push(T* newItem);

        T* pop();

        int getSize();

        ~Heap();
};

#endif