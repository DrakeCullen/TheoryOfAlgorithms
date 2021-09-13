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
MST: MST.o Graph.o LinkedList.o Queue.o Node.o
	$(CC) $(CFLAGS) -o MST MST.o Graph.o LinkedList.o Queue.o Node.o

# To create the object file clockTypeImp.o, we need the source
# files clockTypeImp.cpp, clockType.h:
#

Graph.o: Graph.cpp Graph.h LinkedList.o Queue.o
	$(CC) $(CFLAGS) -c Graph.cpp

LinkedList.o: LinkedList.cpp LinkedList.h Node.o
	$(CC) $(CFLAGS) -c LinkedList.cpp

Queue.o: Queue.cpp Queue.h Node.o
	$(CC) $(CFLAGS) -c Queue.cpp

Node.o: Node.cpp Node.h
	$(CC) $(CFLAGS) -c Node.cpp

clean:
	$(RM) MST *.o *~
