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
default: MST

# To create the executable file clock we need the object files
# clockTypeImp.o, main.o:
#
MST: MST.o Graph.o LinkedList.o PriorityQueue.o AdjacencyList.o Node.o
	$(CC) $(CFLAGS) -o MST MST.o Graph.o LinkedList.o PriorityQueue.o AdjacencyList.o Node.o

# To create the object file clockTypeImp.o, we need the source
# files clockTypeImp.cpp, clockType.h:
#

Graph.o: ./src/Graph.cpp ./include/Graph.h LinkedList.o PriorityQueue.o AdjacencyList.o
	$(CC) $(CFLAGS) -c ./src/Graph.cpp

LinkedList.o: ./src/LinkedList.cpp ./include/LinkedList.h Node.o
	$(CC) $(CFLAGS) -c ./src/LinkedList.cpp

AdjacencyList.o: ./src/AdjacencyList.cpp ./include/AdjacencyList.h LinkedList.o Node.o
	$(CC) $(CFLAGS) -c ./src/AdjacencyList.cpp

PriorityQueue.o: ./src/PriorityQueue.cpp ./include/PriorityQueue.h
	$(CC) $(CFLAGS) -c ./src/PriorityQueue.cpp

Node.o: ./src/Node.cpp ./include/Node.h
	$(CC) $(CFLAGS) -c ./src/Node.cpp

	

clean:
	$(RM) MST *.o *~
