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
default: testMain

# To create the executable file clock we need the object files
# clockTypeImp.o, main.o:
#
testMain: testMain.o
	$(CC) $(CFLAGS) -o testMain testMain.o 

# To create the object file clockTypeImp.o, we need the source
# files clockTypeImp.cpp, clockType.h:
#
	

clean:
	$(RM) MST *.o *~
