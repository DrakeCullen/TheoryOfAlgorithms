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
default: MST journey

# To create the executable file MST we need the MST and Graph object files
MST: MST.o Graph.o
	$(CC) $(CFLAGS) -o MST MST.o Graph.o

# To create the executable file journey we need the journey and Graph object files
journey: journey.o Graph.o
	$(CC) $(CFLAGS) -o journey journey.o Graph.o

# To create the object file Graph, we need the Graph source and header files.
# We also need the linked list and resizable array object files.
Graph.o: ./src/Graph.cpp ./include/Graph.h LinkedList.o ResizableArray.o
	$(CC) $(CFLAGS) -c ./src/Graph.cpp

# To create the object file linked list, we need the linked list source and header files.
# We also need the city object file.
LinkedList.o: ./src/LinkedList.cpp ./include/LinkedList.h City.o
	$(CC) $(CFLAGS) -c ./src/LinkedList.cpp

# To create the object file priority queue, we need the priority queue source and header files.
# We also need the resizable array object file.
PriorityQueue.o: ./src/PriorityQueue.cpp ./include/PriorityQueue.h ResizableArray.o
	$(CC) $(CFLAGS) -c ./src/PriorityQueue.cpp

# To create the object file resizable array, we need the resizable array source and header files.
ResizableArray.o: ./src/ResizableArray.cpp ./include/ResizableArray.h
	$(CC) $(CFLAGS) -c ./src/ResizableArray.cpp

# To create the object file city, we need the city header file.
City.o: ./include/City.h

	
# Make clean removes the executable files and the .o object files.
clean:
	$(RM) MST *.o *~
	$(RM) journey *.o *~
