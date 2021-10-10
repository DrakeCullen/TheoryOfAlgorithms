

#include "../include/Heap.h"

template<typename T>
Heap<T>::Heap(int size) 
{
	heapArr = new Word*[size];
	currentIndex = 0;
}


/**
 * Return the count of the left child of a node. If the node is a leaf, return the node itself to avoid errors.
 * In an array, the left child is always (2 * pos) + 1.
 * O(1). Indexes can be accessed in constant time.
 *  @param int -> The count of the left child
 */
template<typename T>
int Heap<T>::getLeftChild(int index)
{
    if (2 * index + 1 <= currentIndex)
        return heapArr[2 * index + 1]->count;
    else 
        return heapArr[index]->count;
}

/**
 * Return the count of right child of a node. If the node is a leaf, return the node itself to avoid errors.
 * In an array, the right child is always (2 * pos) + 2.
 * O(1). Indexes can be accessed in constant time.
 * @param int -> The count of the right child
 */
template<typename T>
int Heap<T>::getRightChild(int index)
{
    if (2 * index + 2 <= currentIndex)
        return heapArr[2 * index + 2]->count;
    else 
        return heapArr[index]->count;
}

template<typename T>
void Heap<T>::swap(int i, int j)
{
    T temp = heapArr[i];
    heapArr[i] = heapArr[j];
    heapArr[j] = temp;
}


/**
 * After adding a new element as a leaf, move it up until it is in the correct position.
 * O(log(n)). i is divided by roughly 2 everytime. This gives us log(n) runtime.
 */
template<typename T> 
void Heap<T>::moveUp()
{
    int i = currentIndex;
    
    // While the current element is less than its parent, and it is still a valid position
    while (heapArr[i]->count < heapArr[(i - 1) / 2]->count && i >= 0) 
    {
        // Swap the child and parent
        swap(i, (i - 1) / 2);
        // "i" now has the index of the parent
        i = (i - 1) / 2;
    }
}

/**
 * After popping the top element off the heap, move the last element to the top. Make sure it is still a min heap.
 * Continue until ordering is correct or the last level of the tree is reached.
 * O(log(n)). Every loop goes down one level of the tree (multiply i by 2)
 */
template<typename T>
void Heap<T>::moveDown()
{
    int index = 0;
    int current, leftChild, rightChild;

    // Stop when we are at the end of the array, or both children are bigger than the parent
    while (index * 2 + 1 < currentIndex && (heapArr[index]->count > getLeftChild(index) || heapArr[index]->count > getRightChild(index)))
    {
        // Get the parent and its two children
        current = heapArr[index]->count;
        leftChild = getLeftChild(index);
        rightChild = getRightChild(index);

        // If the parent is bigger than one or both of the children, swap the parent and smallest child to correct the order.
        // If that is true, the current index (i) is now pointing to the child node.
        if (leftChild <= rightChild && leftChild < current)
        {
            swap(index, 2 * index + 1);
            index = 2 * index + 1;
        }

        else if (rightChild < current)
        {
            swap(index, 2 * index + 2);
            index = 2 * index + 2;
        }
    }
}

/**
 * Add a new element to the array. If the array is full, enlarge it.
 * Call the moveUp function to reorder the min heap.
 * O(log(n)). The two most significant 'operations' are insert() and moveUp().
 * The function moveUp() is O(log(n)). See above for details.
 * The function insert can be O(n) in the worst case, but, it is only calls enlarge array in powers of 2 (or maybe it isn't ever called if a correct maxSize is passed into the constructor).
 * Therefore, enlargeArray is called at size 128, 256, 512 ... so it is O(1) on average.
 * log(n) dominates, so we have O(log(n))
 * @param T - The new element to add
 */
template<typename T>
void Heap<T>::push(T* newItem)
{
    heapArr[currentIndex] = newItem;
    moveUp();
    currentIndex++;
}

/**
 * Remove the minimum element and replace it with the last item. Decrease the current index by one.
 * Fix the ordering of the min heap with the moveDown function.
 * O(log(n)). As described above, the moveDown function takes O(log(n))
 * @param T - The minimum item in the queue
 */
template<typename T>
T* Heap<T>::pop()
{
    T* topValue = heapArr[0];
    currentIndex--;
    moveDown();
    return topValue;
}

/**
 * Return the size of the priority queue.
 * O(1)
 * @param int - The size of the priority queue
 */
template<typename T>
int Heap<T>::getSize()
{
    return currentIndex;
}

template<typename T>
Heap<T>::~Heap() 
{
	delete[] heapArr;
}
