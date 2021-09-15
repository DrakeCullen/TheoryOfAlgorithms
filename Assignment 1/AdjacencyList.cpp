#include "AdjacencyList.h"

template<typename T> 
AdjacencyList<T>::AdjacencyList(int newSize)
{
    maxSize = newSize;
    currentSize = 0;
    array = new LinkedList<T>[newSize];
}

template<typename T> 
void AdjacencyList<T>::enlargeArray() 
{
    maxSize *= 2;
    LinkedList<T>* n = array;
    LinkedList<T>* newArray = new LinkedList<T>[maxSize];
    for (int i = 0; i <= currentSize; i++)
        newArray[i] = array[i];
    cerr<<newArray<<' '<<array<<' '<<n<<endl;
    
    delete[] array;
    cerr<<newArray<<' '<<array<<endl;
    array = newArray;
    cerr<<newArray<<' '<<array<<endl;
}

template<typename T> 
void AdjacencyList<T>::addEdge(int index, Node<T> *newNode)
{
    array[index].push(newNode);
}

template<typename T> 
void AdjacencyList<T>::calculateSize(int vertex1, int vertex2)
{
    currentSize = vertex1 > currentSize ? vertex2 : currentSize;
    currentSize = vertex2 > currentSize ? vertex2 : currentSize;
    if (currentSize + 1 == maxSize)
        enlargeArray();
}

template<typename T> 
void AdjacencyList<T>::print()
{
    for (int i = 0; i <= currentSize; i++) 
	{
		cout<<i<<": ";
		array[i].print();
	}
}


template<typename T> 
AdjacencyList<T>::~AdjacencyList()
{
    for (unsigned int i = 0; i < maxSize; i++)
        array[i].deleteAll();
    delete[] array;
    array = nullptr;
}


// For priority Queue
template<typename T> 
void AdjacencyList<T>::swap(int firstIndex, int secondIndex)
{
    T temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

template<typename T> 
void AdjacencyList<T>::moveToTop(int lastEntry)
{
    array[0] = array[lastEntry];
    array[lastEntry] = 100000000;
}

template<typename T> 
void AdjacencyList<T>::push(T newItem)
{
    if (currentSize + 1 == maxSize)
        enlargeArray();
    
    array[currentSize++] = newItem;
}


