#include "Queue.h"

template<typename T> 
Queue<T>::Queue() 
{
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	tail->prev = head;
	size = 0;
}

template<typename T> 
int Queue<T>::getSize() 
{ 
	return size; 
}

template<typename T>  
bool Queue<T>::isEmpty() 
{ 
	return size == 0; 
};

template<typename T>  
void Queue<T>::push(T value) 
{
	Node<T>* newNode = new Node<T>();
	newNode->data = value;
	size++;
	
	newNode->prev = tail->prev;
	tail->prev->next = newNode;
	newNode->next = tail;
	tail->prev = newNode;
}


template<typename T>  
T Queue<T>::pop() 
{
	if (size <= 0) return -1;
	
	Node<T>* curr = head->next;
	size--;
	
	head->next = curr->next;
	curr->next->prev = head;
	T value = curr->data;
	delete curr;
	return value;
}


template<typename T>  
void Queue<T>::deleteAll() 
{
	Node<T>* curr = head->next;
	Node<T>* prev = head;

	while (curr != tail) {
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	head->next = tail;
	tail->prev = head;
	size = 0;
}

template<typename T> 
Queue<T>::~Queue()  
{
	deleteAll();
	delete head;
	delete tail;
}