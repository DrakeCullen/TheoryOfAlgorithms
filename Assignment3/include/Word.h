/**
    CSCI-480 - Assignment 3
    @file Word.h
    @author Drake Cullen
	The word object stores the string, a counter that corresponds to the number of time the word appears, and pointers to the last and next word.
*/

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



