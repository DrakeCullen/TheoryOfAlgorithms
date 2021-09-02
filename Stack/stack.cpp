#include<iostream>

template <typename T> struct Node {
	T data;
	Node<T>* next;
};

template <typename T> class Stack {
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	
	public:
		Stack() {
			head = new Node<T>();
			tail = new Node<T>();
			head->next = tail;
			size = 0;
		}
		
		int getSize() { return size; }
		
		bool isEmpty() { return size == 0; };
		
		void push(T value) {
			Node<T>* newNode = new Node<T>();
			newNode->data = value;
			size++;
			
			newNode->next = head->next;
			head->next = newNode;
		}
		
		
		T pop() {
			if (size <= 0) return -1;
			
			Node<T>* curr = head->next;
			size--;
			
			head->next = head->next->next;
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
		
		void deleteAll() {
			Node<T>* curr = head->next;
			Node<T>* prev = head;

			while (curr != tail) {
				prev = curr;
				curr = curr->next;
				delete prev;
			}
			head->next = tail;
			size = 0;
		}
		
		~Stack() {
			deleteAll();
			delete head;
			delete tail;
		}
};

int main() {
	Stack<int> ll;
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
	ll.print();
	std::cout<<"Size: "<<ll.getSize()<<std::endl;
	std::cout<<"IsEmpty: "<<ll.isEmpty()<<std::endl;
	return 0;
}
