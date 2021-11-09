/**
    CSCI-480 - Assignment 1
    @file journey.cpp
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


int main(int argc, char *argv[])
{
   Graph g;
   g.readInput("adjacencyMatrix.txt", "heuristics.txt");
   g.aStar(0,8);
}