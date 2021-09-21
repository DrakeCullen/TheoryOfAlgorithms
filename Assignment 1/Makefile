# This is an example Makefile for a clock program.
# Typing 'make' or 'make clock' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: MST Journey


MST: MST.o Graph.o
	$(CC) $(CFLAGS) -o MST MST.o Graph.o

Journey: Journey.o Graph.o
	$(CC) $(CFLAGS) -o Journey Journey.o Graph.o

Graph.o: ./src/Graph.cpp ./include/Graph.h AdjacencyList.o 
	$(CC) $(CFLAGS) -c ./src/Graph.cpp

LinkedList.o: ./src/LinkedList.cpp ./include/LinkedList.h Node.o
	$(CC) $(CFLAGS) -c ./src/LinkedList.cpp

AdjacencyList.o: ./src/AdjacencyList.cpp ./include/AdjacencyList.h LinkedList.o ResizableArray.o
	$(CC) $(CFLAGS) -c ./src/AdjacencyList.cpp

PriorityQueue.o: ./src/PriorityQueue.cpp ./include/PriorityQueue.h ResizableArray.o
	$(CC) $(CFLAGS) -c ./src/PriorityQueue.cpp

ResizableArray.o: ./src/ResizableArray.cpp ./include/ResizableArray.h
	$(CC) $(CFLAGS) -c ./src/ResizableArray.cpp

Node.o: ./src/Node.cpp ./include/Node.h
	$(CC) $(CFLAGS) -c ./src/Node.cpp

	

clean:
	$(RM) MST *.o *~
	$(RM) Journey *.o *~
