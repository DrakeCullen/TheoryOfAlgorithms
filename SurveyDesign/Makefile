COMPILER = g++
COMPILER_FLAGS = -Wall -std=c++17
PROGRAM_NAME = main.o
CPP_FILES = main.cpp 

build:
	rm -f $(PROGRAM_NAME) *.o
	$(COMPILER) $(COMPILER_FLAGS) $(CPP_FILES) -o $(PROGRAM_NAME)
	./$(PROGRAM_NAME)

clean:
	rm -f $(PROGRAM_NAME) *.o