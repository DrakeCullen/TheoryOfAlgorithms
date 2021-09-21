/**
    CSCI-480 - Assignment 1
    @file MST.cpp
    @author Drake Cullen
*/

#include "./include/Graph.h"

int getCityIndex(char *argv[], int argValue, Graph &g)
{
    string city = argv[argValue];
    city += ' ';
    city += argv[argValue + 1];
    int index = g.findCityIndex(city);
    if (index == -1)
        cout << city << " is an invalid city! \n";
    return index;
}

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        cout << "Pass a file as a parameter! \n";
        return 0;
    }
    Graph g;
    g.readInput(argv[1]);
    if (argc == 6)
    {
        int startIndex = getCityIndex(argv, 2, g);
        if (startIndex == -1)
            return 0;
        int destinationIndex = getCityIndex(argv, 4, g);
        if (destinationIndex == -1)
            return 0;
        g.dijkstra(startIndex, destinationIndex);
    }
    else
        cout << "Pass in a start and destination city! \n";    
}