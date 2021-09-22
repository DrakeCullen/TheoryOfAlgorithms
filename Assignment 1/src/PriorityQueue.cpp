/**
    CSCI-480 - Assignment 1
    @file PriorityQueue.cpp
    @author Drake Cullen
    Priority queue implemented using a min heap
*/

#include "../include/PriorityQueue.h"

/**
 * After adding a new element as a leaf, move it up until it is in the correct position.
 * O(log(n)). i is divided by roughly 2 everytime. This gives us log(n) runtime.
 */
template<typename T> 
void PriorityQueue<T>::moveUp()
{
    int i = currentIndex;
    
    // While the current element is less than its parent, and it is still a valid position
    while (array.getElement(i)->weight < array.getElement((i - 1) / 2)->weight && i >= 0) 
    {
        // Swap the child and parent
        array.swap(i, (i - 1) / 2);
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
    int current, leftChild, rightChild;

    // Stop when we are at the end of the array, or both children are bigger than the parent
    while (index * 2 + 1 < currentIndex && (array.getElement(index)->weight > getLeftChild(index) || array.getElement(index)->weight > getRightChild(index)))
    {
        // Get the parent and its two children
        current = array.getElement(index)->weight;
        leftChild = getLeftChild(index);
        rightChild = getRightChild(index);

        // If the parent is bigger than one or both of the children, swap the parent and smallest child to correct the order.
        // If that is true, the current index (i) is now pointing to the child City.
        if (leftChild <= rightChild && leftChild < current)
        {
            array.swap(index, 2 * index + 1);
            index = 2 * index + 1;
        }

        else if (rightChild < current)
        {
            array.swap(index, 2 * index + 2);
            index = 2 * index + 2;
        }
    }
}

/**
 * Return the left child of a City. If the City is a leaf, return the City itself to avoid errors.
 * In an array, the left child is always (2 * pos) + 1.
 * O(1). Indexes can be accessed in constant time.
 *  @param index -> The index of the parent City
 */
template<typename T>
int PriorityQueue<T>::getLeftChild(int index)
{
    if (2 * index + 1 <= currentIndex)
        return array.getElement(2 * index + 1)->weight;
    else 
        return array.getElement(index)->weight;
}

/**
 * Return the right child of a City. If the City is a leaf, return the City itself to avoid errors.
 * In an array, the right child is always (2 * pos) + 2.
 * O(1). Indexes can be accessed in constant time.
 * @param index -> The index of the parent City
 */
template<typename T>
int PriorityQueue<T>::getRightChild(int index)
{
    if (2 * index + 2 <= currentIndex)
        return array.getElement(2 * index + 2)->weight;
    else 
        return array.getElement(index)->weight;
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
    array.insert(newItem);
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
    T topValue = array.pop();
    currentIndex--;
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
    //delete[] array;
}