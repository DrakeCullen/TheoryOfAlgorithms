#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node {
public:
	string data;
	int index;
	int weight;
	int number;
	int from;
	Node* next;
	Node* prev;
};

#endif
