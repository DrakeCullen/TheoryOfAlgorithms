/**
    CSCI-480 - Assignment 1
    @file journey.cpp
    @author Drake Cullen
*/

#include "./include/Graph.h"
#include <chrono>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Pass a file as a parameter! \n";
        return 0;
    }
    Graph g;
    g.readInput(argv[1]);
    if (argc == 4)
    {
        int startIndex = g.findCityIndex(argv[2]);
        if (startIndex == -1)
        {
            cout << argv[2] << " is an invalid city! \n";
            return 0;
        }
        int destinationIndex = g.findCityIndex(argv[3]);
        if (destinationIndex == -1)
        {
            cout << argv[3] << " is an invalid city! \n";
            return 0;
        }
        // This includes print time. Move inside the functions to only get calculation time...
        auto start = chrono::steady_clock::now();
        g.dijkstra(startIndex, destinationIndex);
        auto end = chrono::steady_clock::now();
        cout << "Time taken to find the shortest path: " << double(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000000 << " seconds. \n";
    }
    else
        cout << "Pass in a start and destination city! \n";
}