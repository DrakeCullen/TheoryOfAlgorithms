#include "../include/LinkedList.h"
#include "../src/LinkedList.cpp"
#include <assert.h>

void addCity(LinkedList<string> &ll, string data)
{
    City* newCity = new City;
    newCity->data = data;
    ll.push(newCity);
}

void lladdItems()
{
    LinkedList<string> ll;
    addCity(ll, "3");
    addCity(ll, "20");
    addCity(ll, "14");
    addCity(ll, "12");
    addCity(ll, "31");
    addCity(ll, "7");
    addCity(ll, "11");
    addCity(ll, "13");
    addCity(ll, "7");
    assert( ll.pop() == "7");
}

void llcheckingSize()
{
    LinkedList<string> ll;
    assert( ll.getSize() == 0);
    addCity(ll, "45");
    assert( ll.getSize() == 1);
    addCity(ll, "20");
    assert( ll.getSize() == 2);
    addCity(ll, "14");
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
    LinkedList<string>  ll;
    addCity(ll, "45");
    addCity(ll, "20");
    addCity(ll, "14");
    addCity(ll, "12");
    addCity(ll, "31");
    addCity(ll, "7");
    addCity(ll, "11");
    addCity(ll, "13");
    addCity(ll, "7");
    assert( ll.pop() == "7");
    assert( ll.pop() == "13");
    assert( ll.pop() == "11");
    assert( ll.pop() == "7");
    assert( ll.pop() == "31");
    assert( ll.pop() == "12");
    assert( ll.pop() == "14");
    assert( ll.pop() == "20");
    assert( ll.pop() == "45");
}