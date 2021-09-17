/**
    CSCI-480 - Assignment 1
    @file PriorityQueue.cpp
    @author Drake Cullen
*/

#include "../include/PriorityQueue.h"

/**
 * Default Constructor that allocates memory for an array of type T. Default size is 2.
 * The min heap is stored in the array data structure.
 * O(1)
 */
template<typename T> 
PriorityQueue<T>::PriorityQueue(int size)
{
    maxSize = size;
    array = new T[size];
}

/**
 * After adding a new element as a leaf, move it up until it is in the correct position.
 * O(log(n)). i is divided by roughly 2 everytime. This gives us log(n) runtime.
 */
template<typename T> 
void PriorityQueue<T>::moveUp()
{
    int i = currentIndex;
    
    // While the current element is less than its parent, and it is still a valid position
    while (array[i] < array[(i - 1) / 2] && i >= 0) 
    {
        // Swap the child and parent
        swap(i, (i - 1) / 2);
        // "I" now has the index of the parent
        i = (i - 1) / 2;
    }
}

/**
 * After popping the top element off the heap, move the last element to the top. Make sure it is still a min heap.
 * Continue until ordering is correct or the last level of the tree is reached.
 * O(log(n)). Every loop goes down one level of the tree (multiply i by 2)
 */
template<typename T>
void PriorityQueue<T>::moveDown()
{
    int index = 0;
    T current, leftChild, rightChild;

    // Stop when we are at the end of the array, or both children are bigger than the parent
    while (index * 2 + 1 < currentIndex && (array[index] > getLeftChild(index) || array[index] > getRightChild(index)))
    {
        // Get the parent and its two children
        current = array[index];
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
 * Return the left child of a node. If the node is a leaf, return the node itself to avoid errors.
 * In an array, the left child is always (2 * pos) + 1.
 * O(1). Indexes can be accessed in constant time.
 *  @param index -> The index of the parent node
 */
template<typename T>
T PriorityQueue<T>::getLeftChild(int index)
{
    if (2 * index + 1 <= currentIndex)
        return array[2 * index + 1];
    else 
        return array[index];
}

/**
 * Return the right child of a node. If the node is a leaf, return the node itself to avoid errors.
 * In an array, the right child is always (2 * pos) + 2.
 * O(1). Indexes can be accessed in constant time.
 * @param index -> The index of the parent node
 */
template<typename T>
T PriorityQueue<T>::getRightChild(int index)
{
    if (2 * index + 2 <= currentIndex)
        return array[2 * index + 2];
    else 
        return array[index];
}

/**
 * Swap two nodes in the array.
 * O(1). Indexes can be accessed in constant time. 
 * @param firstIndex -> The index of the first node
 * @param secondIndex -> The index of the second node
 */
template<typename T>
void PriorityQueue<T>::swap(int firstIndex, int secondIndex)
{
    T temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

/**
 * If the array becomes full, we must allocate new space on the heap and delete the old array.
 * This is inspired by the way vectors work in c++. Everytime we make a new array, the size is doubled.
 * O(n). Iterate over and copy every element.
 */
template<typename T> 
void PriorityQueue<T>::enlargeArray() 
{
    maxSize *= 2;
    T* newArray = new T[maxSize];

    for (int i = 0; i <= currentIndex; i++)
        newArray[i] = array[i];

    delete[] array;
    array = newArray;
}

/**
 * Add a new element to the array. If the array is full, enlarge it.
 * Call the moveUp function to reorded the min heap.
 * O(log(n)). The two most significant 'operations' are enlargeArray() and moveUp().
 * The function moveUp() is O(log(n)). See above for details.
 * The function enlargeArray is O(n), but, it is only called in powers of 2 (or maybe it isn't ever called if a correct maxSize is passed into the constructor).
 * Therefore, enlargeArray is called at size 4, 8, 16, 32, 64, 128 ... so the calls are O(log(n)) in this function.
 * log(n) + log(n) = 2log(n) = O(log(n))
 * @param newItem -> The new element to add
 */
template<typename T>
void PriorityQueue<T>::push(T newItem)
{
    if (currentIndex + 1 >= maxSize)
        enlargeArray();
    array[currentIndex] = newItem;
    moveUp();
    currentIndex++;
}

/**
 * Remove the minimum element and replace it with the last item. Decrease the current index by one.
 * Fix the ordering of the min heap with the moveDown function.
 * O(log(n)). As described above, the moveDown function takes O(log(n))
 */
template<typename T>
T PriorityQueue<T>::pop()
{
    T topValue = array[0];
    currentIndex--;
    array[0] = array[currentIndex];
    moveDown();
    return topValue;
}

/**
 * Return the size of the priority queue.
 * O(1)
 */
template<typename T>
int PriorityQueue<T>::getSize()
{
    return currentIndex;
}

/**
 * Default destructor. Free up the memory allocated on the heap.
 * O(n). Iterate over and dele every element.
 */
template<typename T> 
PriorityQueue<T>::~PriorityQueue()
{
    delete[] array;
}