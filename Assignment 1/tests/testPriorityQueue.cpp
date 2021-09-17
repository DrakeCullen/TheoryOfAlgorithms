#include "../include/PriorityQueue.h"
#include "../src/PriorityQueue.cpp"
#include <assert.h>

void pqaddItems()
{
    PriorityQueue<int> pq;
    pq.push(45);
    pq.push(20);
    pq.push(14);
    pq.push(12);
    pq.push(31);
    pq.push(7);
    pq.push(11);
    pq.push(13);
    pq.push(7);
    assert(pq.pop() == 7);
}

void pqcheckingSize()
{
    PriorityQueue<int> pq;
    assert(pq.getSize() == 0);
    pq.push(45);
    assert(pq.getSize() == 1);
    pq.push(20);
    assert(pq.getSize() == 2);
    pq.push(14);
    assert(pq.getSize() == 3);
    pq.pop();
    assert(pq.getSize() == 2);
    pq.pop();
    assert(pq.getSize() == 1);
    pq.pop();
    assert(pq.getSize() == 0);
}

void pqcheckOrder()
{
    PriorityQueue<int> pq;
    pq.push(45);
    pq.push(20);
    pq.push(14);
    pq.push(12);
    pq.push(31);
    pq.push(7);
    pq.push(11);
    pq.push(13);
    pq.push(7);
    assert(pq.pop() == 7);
    assert(pq.pop() == 7);
    assert(pq.pop() == 11);
    assert(pq.pop() == 12);
    assert(pq.pop() == 13);
    assert(pq.pop() == 14);
    assert(pq.pop() == 20);
    assert(pq.pop() == 31);
    assert(pq.pop() == 45);
}