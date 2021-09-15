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

        void moveUp();

        T getLeftChild(int index);

        T getRightChild(int index);

        void moveDown();

    public:
        PriorityQueue(int size);

        void push(T newItem);

        T pop();

        int getSize();

        void print();
        ~PriorityQueue();
};

#endif