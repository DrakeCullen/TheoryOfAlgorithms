

#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>

using namespace std;

class Word {
public:
	// The name of the city
	string data;
	// The number of times the word appears
	int count;

	Word* next;
	Word* prev;
};

#endif



