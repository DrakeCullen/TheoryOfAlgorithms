/**
    CSCI-480 - Assignment 1
    @file MST.cpp
    @author Drake Cullen
*/

/**
    I declare that all material in this assessment task is my work except where there is clear acknowledgement or reference to the work of others. 
    I further declare that I have complied and agreed to the CMU Academic Integrity Policy at the University website.
    http://www.coloradomesa.edu/student-services/documents
    Author’s Name: Drake Cullen 
    UID(700#): 700480375
    Date: 9/28/2021
*/

#include "./include/Graph.h"
#include <chrono>

int main(int argc, char *argv[]) {
    // If no file is passed
    if (argc < 2)
    {
        cout << "Pass a file as a parameter! \n";
        return 0;
    }

    Graph g;
    g.readInput(argv[1]);

    // If the correct number of parameters are passed
    if (argc == 3)
    {
        string cityName = argv[2];
        int startNode = g.findCityIndex(cityName);
        if (startNode == -1)
        {
            cout << argv[2] << " is an invalid city! \n";
            return 0;
        }

        // If the city is valid
        g.MST(startNode);
    }
    else
        cout << "Enter a start city! \n";
    return 0;
}