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

        void addEdge(int index, Node<T> *newNode);

        void checkNeighbors(bool visited[], PriorityQueue<Node<T>> &pq, int index);

        void checkShortestPath(bool visited[], PriorityQueue<Node<T>> &pq, int index, int distance[], int prev[]);

        // This isn't needed?
        void calculateSize();

        void print();

        ~AdjacencyList();
};

#endif