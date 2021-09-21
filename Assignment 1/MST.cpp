/**
    CSCI-480 - Assignment 1
    @file MST.cpp
    @author Drake Cullen
*/

#include "./include/Graph.h"
#include <chrono>

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        cout << "Pass a file as a parameter! \n";
        return 0;
    }

    Graph g;
    g.readInput(argv[1]);
    if (argc == 3)
    {
        string cityName = argv[2];
        int startNode = g.findCityIndex(cityName);
        if (startNode == -1)
        {
            cout << argv[2] << " is an invalid city! \n";
            return 0;
        }
        auto start = chrono::steady_clock::now();
        g.MST(startNode);
        auto end = chrono::steady_clock::now();
        cout << "Time taken to find the Minimum Spanning Tree: " << double(chrono::duration_cast<chrono::microseconds>(end-start).count()) / 1000000 << " seconds. \n";
    }
    else
        cout << "Enter a start city! \n";
    return 0;
}