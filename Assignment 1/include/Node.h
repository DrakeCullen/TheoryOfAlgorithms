#ifndef NODE_H
#define NODE_H
#include <string>

template <typename T>  class Node {
public:
	T data;
	int index;
	int weight;
	int number;
	int from;
	Node<T>* next;
	Node<T>* prev;
};

#endif
