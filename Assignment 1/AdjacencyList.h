#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "LinkedList.h"
#include "LinkedList.cpp"

template <typename T>
class AdjacencyList
{
    private:
        int maxSize;
        int currentSize;
        LinkedList<T>* array;

        void enlargeArray();

    public:
        AdjacencyList(int newSize = 16);

        void push(T newItem);

        T operator[](T index);

        void addEdge(int index, Node<T> *newNode);

        void swap(int firstIndex, int secondIndex);

        void moveToTop(int lastEntry);

        void calculateSize(int vertex1, int vertex2);

        void print();

        ~AdjacencyList();
};

#endif