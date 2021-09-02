#include<iostream>

template <typename T> struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T> class LinkedList {
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	
	public:
		LinkedList() {
			head = new Node<T>();
			tail = new Node<T>();
			head->next = tail;
			tail->prev = head;
			size = 0;
		}
		
		int getSize() { return size; }
		
		bool isEmpty() { return size == 0; };
		
		void push(T value, int pos = 0) {
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
		
		
		T pop(int pos = 0) {
			if (pos > size) return -1;
			
			Node<T>* curr = head->next;
			Node<T>* prev = head;
			size--;
			
			for (int i = 0; i < pos; i++) {
				curr = curr->next;
				prev = prev->next;
			}
			
			curr->next->prev = prev;
			prev->next = curr->next;
			T value = curr->data;
			delete curr;
			return value;
		}
		
		void print() {
			Node<T>* curr = head->next;
			while(curr != tail) {
				std::cout<<curr->data<<' ';
				curr = curr->next;
			}
			std::cout<<std::endl;
		}
		
		void printReverse() {
			Node<T>* curr = tail->prev;
			while(curr != head) {
				std::cout<<curr->data<<' ';
				curr = curr->prev;
			}
			std::cout<<std::endl;
		}
		
		void deleteAll() {
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
		
		~LinkedList() {
			deleteAll();
			delete head;
			delete tail;
		}
};

int main() {
	LinkedList<int> ll;
	ll.push(5);
	ll.push(8);
	ll.push(3);
	ll.push(1, 3);
	ll.print();
	ll.printReverse();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	ll.pop(1);
	ll.print();
	ll.printReverse();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	ll.deleteAll();
	ll.print();
	ll.printReverse();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	std::cout<<"IsEmpty: "<<ll.isEmpty()<<std::endl;
	ll.push(3);
	ll.print();
	ll.printReverse();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	std::cout<<"IsEmpty: "<<ll.isEmpty()<<std::endl;
	return 0;
}
