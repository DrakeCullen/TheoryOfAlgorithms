#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "LinkedList.h"
#include "../src/LinkedList.cpp"
#include "ResizableArray.h"
#include "../src/ResizableArray.cpp"

template <typename T>
class AdjacencyList
{
    private:
        ResizableArray<LinkedList<T>> array;

    public:
        AdjacencyList();

        void addEdge(int index, Node *newNode);

        void checkNeighbors(bool visited[], PriorityQueue<Node> &pq, int index);

        void checkShortestPath(bool visited[], PriorityQueue<Node> &pq, int index, int distance[], int prev[]);

        ~AdjacencyList();
};

#endif