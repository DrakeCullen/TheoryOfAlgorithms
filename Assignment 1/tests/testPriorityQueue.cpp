#include "testLinkedList.cpp"
#include <assert.h>

void pqaddItems()
{
    PriorityQueue<string> pq;
    addCity(pq, "45");
    addCity(pq, "20");
    addCity(pq, "14");
    addCity(pq, "12");
    addCity(pq, "31");
    addCity(pq, "7");
    addCity(pq, "11");
    addCity(pq, "13");
    addCity(pq, "7");
    assert(pq.pop() == "7");
}

void pqcheckingSize()
{
    PriorityQueue<string> pq;
    assert(pq.getSize() == 0);
    pq.push("45");
    assert(pq.getSize() == 1);
    pq.push("20");
    assert(pq.getSize() == 2);
    pq.push("14");
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
    PriorityQueue<string> pq;
    addCity(pq, "45");
    addCity(pq, "20");
    addCity(pq, "14");
    addCity(pq, "12");
    addCity(pq, "31");
    addCity(pq, "7");
    addCity(pq, "11");
    addCity(pq, "13");
    addCity(pq, "7");
    assert(pq.pop() == "7");
    assert(pq.pop() == "7");
    assert(pq.pop() == "11");
    assert(pq.pop() == "12");
    assert(pq.pop() == "13");
    assert(pq.pop() == "14");
    assert(pq.pop() == "20");
    assert(pq.pop() == "31");
    assert(pq.pop() == "45");
}