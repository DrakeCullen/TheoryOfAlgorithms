#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "LinkedList.h"
#include "../src/LinkedList.cpp"

template <typename T>
class AdjacencyList
{
    private:
        int maxSize;
        int currentSize;
        LinkedList<T>* array;

        void enlargeArray();

    public:
        AdjacencyList(int newSize = 2);

        T operator[](T index);

        void addEdge(T index, Node<T> *newNode);

        // This isn't needed?
        void calculateSize(int vertex1, int vertex2);

        void print();

        ~AdjacencyList();
};

#endif