#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>

using namespace std;

template <typename T> 
class PriorityQueue 
{
    private:
        T* array;
        int currentIndex = 0;
        int maxSize = 0;

        void moveUp();

        T getLeftChild(int index);

        T getRightChild(int index);

        void moveDown();

        void enlargeArray();

        void swap(int firstIndex, int secondIndex);

    public:
        PriorityQueue(int size = 2);

        void push(T newItem);

        T pop();

        int getSize();

        void print();

        ~PriorityQueue();
};

#endif