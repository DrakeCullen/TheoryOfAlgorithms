/**
    CSCI-480 - Assignment 1
    @file MST.cpp
    @author Drake Cullen
*/

#include "./include/Graph.h"

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        cout << "Pass a file as a parameter! \n";
        return 0;
    }
    Graph g;
    g.readInput(argv[1]);
    if (argc == 4)
    {
        string cityName = argv[2];
        cityName += ' ';
        cityName += argv[3];
        int startNode = g.findCityIndex(cityName);
        if (startNode == -1)
            g.MST(0);
        else
            g.MST(startNode);
    }
    else
        g.MST(0);
}