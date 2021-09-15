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
void LinkedList<T>::push(Node<T>* newNode) 
{
	newNode->next = head->next;
	head->next->prev = newNode;
	newNode->prev = head;
	head->next = newNode;
	size++;
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

/*template<typename T>  
void LinkedList<T>::checkForAllElements(Queue<T> &queue, bool visited[]) {
            Node<T>* curr = head->next;
            while (curr != tail) {
				if (!visited[curr->value]) {
					visited[curr->value] = 1;
					queue.push(curr->value);
				}
                curr = curr->next;
            }
        }
*/

template<typename T> 
void LinkedList<T>::deleteAll() 
{
	cout<<"delete";
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
	delete head;
	delete tail;
}

template<typename T> 
LinkedList<T>::~LinkedList() 
{
	//deleteAll();
	//delete head;
	//delete tail;
}

