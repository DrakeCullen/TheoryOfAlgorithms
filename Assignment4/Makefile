# Here is the makefile for the MST and shortest path
# Type make to create MST and journey. You can also make one of the executable files. For instance, make MST
#

# Creating variables
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# CC holds the value g++
CC = g++
CFLAGS  = -g -Wall

# the default target is to make MST and journey
all: main


# To create the executable file journey we need the journey and Graph object files
main: main.o Graph.o 
	$(CC) $(CFLAGS) -o main main.o Graph.o

# To create the object file Graph, we need the Graph source and header files.
# We also need the linked list and resizable array object files.
Graph.o: ./src/Graph.cpp Node.o
	$(CC) $(CFLAGS) -c ./src/Graph.cpp

# To create the object file city, we need the city header file.
Node.o: ./include/Node.h

	
# Make clean removes the executable files and the .o object files.
clean:
	$(RM) main *.o *~
