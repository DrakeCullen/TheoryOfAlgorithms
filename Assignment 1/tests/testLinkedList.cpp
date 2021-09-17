#include "../include/LinkedList.h"
#include "../src/LinkedList.cpp"
#include <assert.h>

void addNode(LinkedList<int> &ll, int data)
{
    Node<int>* newNode = new Node<int>;
    newNode->data = data;
    ll.push(newNode);
}

void lladdItems()
{
    LinkedList<int> ll;
    addNode(ll, 3);
    addNode(ll, 20);
    addNode(ll, 14);
    addNode(ll, 12);
    addNode(ll, 31);
    addNode(ll, 7);
    addNode(ll, 11);
    addNode(ll, 13);
    addNode(ll, 7);
    assert( ll.pop() == 7);
}

void llcheckingSize()
{
    LinkedList<int> ll;
    assert( ll.getSize() == 0);
    addNode(ll, 45);
    assert( ll.getSize() == 1);
    addNode(ll, 20);
    assert( ll.getSize() == 2);
    addNode(ll, 14);
    assert( ll.getSize() == 3);
    ll.pop();
    assert( ll.getSize() == 2);
    ll.pop();
    assert( ll.getSize() == 1);
    ll.pop();
    assert( ll.getSize() == 0);
}

void llcheckOrder()
{
    LinkedList<int>  ll;
    addNode(ll, 45);
    addNode(ll, 20);
    addNode(ll, 14);
    addNode(ll, 12);
    addNode(ll, 31);
    addNode(ll, 7);
    addNode(ll, 11);
    addNode(ll, 13);
    addNode(ll, 7);
    assert( ll.pop() == 7);
    assert( ll.pop() == 13);
    assert( ll.pop() == 11);
    assert( ll.pop() == 7);
    assert( ll.pop() == 31);
    assert( ll.pop() == 12);
    assert( ll.pop() == 14);
    assert( ll.pop() == 20);
    assert( ll.pop() == 45);
}