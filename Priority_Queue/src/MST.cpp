#include <iostream>
#include <climits>

#include "PriorityQueue.h"
#include "PriorityQueue.cpp"

using namespace std;



int main() 
{
    PriorityQueue<int> da;

    da.push(45);
    da.push(20);
    da.push(14);
    da.push(12);
    da.push(31);
    da.push(7);
    da.push(11);
    da.push(13);
    da.push(7);

    while(da.getSize())
        cout<<da.pop()<<' ';
}