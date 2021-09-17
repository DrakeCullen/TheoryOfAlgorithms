#include "testPriorityQueue.cpp"
#include "testLinkedList.cpp"

#include <iostream>

using namespace std;

int main()
{
    pqaddItems();
    pqcheckingSize();
    pqcheckOrder();
    cout<<"Priority Queue tests succesful!"<<endl;
    lladdItems();
    llcheckingSize();
    llcheckOrder();
    cout<<"Linked List tests succesful!"<<endl;

}