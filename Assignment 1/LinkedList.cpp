#include "LinkedList.h"

template<typename T> 
LinkedList<T>::LinkedList() 
{
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	tail->prev = head;
	size = 0;
}

template<typename T> 
int LinkedList<T>::getSize() 
{ 
	return size; 
}

template<typename T> 
bool LinkedList<T>::isEmpty() 
{ 
	return size == 0; 
};

template<typename T> 
void LinkedList<T>::push(T value, int pos) 
{
	if (pos > size) return;
	
	Node<T>* curr = head;
	Node<T>* newNode = new Node<T>();
	newNode->data = value;
	size++;
	
	for (int i = 0; i < pos; i++) 
		curr = curr->next;
	
	curr->next->prev = newNode;
	newNode->next = curr->next;
	curr->next = newNode;
	newNode->prev = curr;
}

template<typename T> 
T LinkedList<T>::pop(int pos) 
{
	if (pos > size) return -1;
	
	Node<T>* curr = head->next;
	Node<T>* prev = head;
	size--;
	
	for (int i = 0; i < pos; i++) 
	{
		curr = curr->next;
		prev = prev->next;
	}
	
	curr->next->prev = prev;
	prev->next = curr->next;
	T value = curr->data;
	delete curr;
	return value;
}

template<typename T> 
void LinkedList<T>::print() 
{
	Node<T>* curr = head->next;
	while(curr != tail) 
	{
		cout<<curr->data<<' ';
		curr = curr->next;
	}
	cout<<std::endl;
}

template<typename T> 
void LinkedList<T>::printReverse() 
{
	Node<T>* curr = tail->prev;
	while(curr != head) 
	{
		cout<<curr->data<<' ';
		curr = curr->prev;
	}
	cout<<std::endl;
}

template<typename T>  
void Queue<T>::checkForAllElements(Queue<T> &queue, bool visited[]) {
            Node<T>* curr = head->next;
            while (curr != tail) {
				if (!visited[curr->value]) {
					visited[curr->value] = 1;
					queue.push(curr->value);
				}
                curr = curr->next;
            }
        }


template<typename T> 
void LinkedList<T>::deleteAll() 
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
LinkedList<T>::~LinkedList() 
{
	deleteAll();
	delete head;
	delete tail;
}

