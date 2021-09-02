#include<iostream>

template <typename T> struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T> class Queue {
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	
	public:
		Queue() {
			head = new Node<T>();
			tail = new Node<T>();
			head->next = tail;
			tail->prev = head;
			size = 0;
		}
		
		int getSize() { return size; }
		
		bool isEmpty() { return size == 0; };
		
		void push(T value) {
			Node<T>* newNode = new Node<T>();
			newNode->data = value;
			size++;
			
			newNode->prev = tail->prev;
			tail->prev->next = newNode;
			newNode->next = tail;
			tail->prev = newNode;
		}
		
		
		T pop() {
			if (size <= 0) return -1;
			
			Node<T>* curr = head->next;
			size--;
			
			head->next = curr->next;
			curr->next->prev = head;
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
		
		~Queue() {
			deleteAll();
			delete head;
			delete tail;
		}
};

int main() {
	Queue<int> ll;
	ll.push(5);
	ll.push(8);
	ll.push(3);
	ll.push(1);
	ll.print();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	ll.pop();
	ll.print();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	ll.deleteAll();
	ll.print();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	std::cout<<"IsEmpty: "<<ll.isEmpty()<<std::endl;
	ll.push(3);
	ll.push(1);
	ll.print();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	std::cout<<"IsEmpty: "<<ll.isEmpty()<<std::endl;
	ll.pop();
	ll.pop();
	ll.print();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	std::cout<<"IsEmpty: "<<ll.isEmpty()<<std::endl;
	return 0;
}
