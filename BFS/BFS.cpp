#include<iostream>

using namespace std;

template <typename T> struct QueueNode {
	T data;
	QueueNode<T>* next;
	QueueNode<T>* prev;
};

template <typename T> class Queue {
	private:
		QueueNode<T>* head;
		QueueNode<T>* tail;
		int size;
	
	public:
		Queue() {
			head = new QueueNode<T>();
			tail = new QueueNode<T>();
			head->next = tail;
			tail->prev = head;
			size = 0;
		}
		
		int getSize() { return size; }
		
		bool isEmpty() { return size == 0; };
		
		void push(T value) {
			QueueNode<T>* newNode = new QueueNode<T>();
			newNode->data = value;
			size++;
			
			newNode->prev = tail->prev;
			tail->prev->next = newNode;
			newNode->next = tail;
			tail->prev = newNode;
		}
		
		
		T pop() {
			if (size <= 0) return -1;
			
			QueueNode<T>* curr = head->next;
			size--;
			
			head->next = curr->next;
			curr->next->prev = head;
			T value = curr->data;
			delete curr;
			return value;
		}
		
		void deleteAll() {
			QueueNode<T>* curr = head->next;
			QueueNode<T>* prev = head;

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

template <typename T> struct Node {
	T value;
    T weight;
	Node<T>* next;
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
			size = 0;
		}
		
		int getSize() { return size; }
		
		bool isEmpty() { return size == 0; };
		
		void push(Node<T> *newNode) {
			size++;
			
			newNode->next = head->next;
			head->next = newNode;
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
			
			prev->next = curr->next;
			T value = curr->value;
			delete curr;
			return value;
		}

        void print() {
			Node<T>* curr = head->next;
			while(curr != tail) {
				std::cout<<curr->value<<' ';
				curr = curr->next;
			}
			std::cout<<std::endl;
		}

        void checkForAllElements(Queue<T> &queue, bool visited[]) {
            Node<T>* curr = head->next;
            while (curr != tail) {
				if (!visited[curr->value]) {
					visited[curr->value] = 1;
					queue.push(curr->value);
				}
                curr = curr->next;
            }
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
		
		~LinkedList() {
			deleteAll();
			delete head;
			delete tail;
		}
};

template <typename T> class Graph {
private:
	bool* visited;
	LinkedList<T>* adj;
    int size;
	
public:
    Graph(int newSize) {
        size = newSize;
        visited = new bool[size];
        adj = new LinkedList<T>[size];
    }

	void addEdge(int v1, int v2, int w=0) { 
        Node<T>* newNode = new Node<T>;
        newNode->value = v2;
        newNode->weight = w;
        adj[v1].push(newNode); 
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout<<i<<": ";
            adj[i].print();
        }
    }
	
	void bfs(int s) {
		Queue<T> queue;
		visited[s] = 1;
		queue.push(s);
		while(!queue.isEmpty()) {
			int v = queue.pop();
			visited[v] = 1;
            cout<<v<<' ';
            adj[v].checkForAllElements(queue, visited);
		}
	}
};


int main() {
	Graph<int> g(13);
    g.addEdge(0, 9);
    g.addEdge(0, 1);
    g.addEdge(1, 8);
    g.addEdge(9, 8);
    g.addEdge(8, 7);
    g.addEdge(7, 10);
    g.addEdge(7, 11);
    g.addEdge(7, 3);
    g.addEdge(7, 6);
    g.addEdge(10, 11);
    g.addEdge(6, 5);
    g.addEdge(5, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 2);
    //g.print();
    g.bfs(0);
	return 0;
}
