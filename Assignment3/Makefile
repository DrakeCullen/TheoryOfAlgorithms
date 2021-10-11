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
all: ass3j

# To create the executable file MST we need the MST and Graph object files
ass3j: ass3j.o Hashtable.o
	$(CC) $(CFLAGS) -o ass3j ass3j.o Hashtable.o

Hashtable.o: ./src/Hashtable.cpp ./include/Hashtable.h LinkedList.o
	$(CC) $(CFLAGS) -c ./src/Hashtable.cpp

# To create the object file linked list, we need the linked list source and header files.
# We also need the city object file.
LinkedList.o: ./src/LinkedList.cpp ./include/LinkedList.h Word.o Heap.o
	$(CC) $(CFLAGS) -c ./src/LinkedList.cpp

Heap.o: ./src/Heap.cpp ./include/Heap.h Word.o
	$(CC) $(CFLAGS) -c ./src/Heap.cpp

# To create the object file word, we need the word header file.
Word.o: ./include/Word.h

	
# Make clean removes the executable files and the .o object files.
clean:
	$(RM) ass3j *.o *~
