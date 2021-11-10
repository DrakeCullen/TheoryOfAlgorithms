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
    if (argc < 3 || argc > 4)
    {
        cout << "Pass an input file with weights and an input file with heuristics as parameters! \n";
        return 0;
    }
    else 
    {
        Graph g;
        g.readInput(argv[1], argv[2]);
        int startCity, endCity;

        // Clear the console
        cout << "\x1B[2J\x1B[H";
        
        while (true)
        {
            cout<<"Enter a start and end city, or enter 0 0 to stop the program: ";
            cin>>startCity>>endCity;
            if (startCity == 0 && endCity == 0) break;
            try {
                g.aStar(startCity, endCity);
            } catch (exception e)
            {
                cout<<"There was a problem with your input!";
            }
            cout<<endl<<endl<<endl<<endl;
        }
    }
    
}