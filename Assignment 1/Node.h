#ifndef NODE_H
#define NODE_H
#include <string>

template <typename T>  class Node {
public:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

#endif
