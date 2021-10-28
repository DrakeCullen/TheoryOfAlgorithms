COMPILER = g++
COMPILER_FLAGS = -Wall -std=c++17
PROGRAM_NAME = main.o
CPP_FILES = main.cpp 

test1:
	rm -f $(PROGRAM_NAME) *.o
	$(COMPILER) $(COMPILER_FLAGS) $(CPP_FILES) -o $(PROGRAM_NAME)
	./$(PROGRAM_NAME)

test2:
	rm -f $(PROGRAM_NAME) *.o
	$(COMPILER) $(COMPILER_FLAGS) $(CPP_FILES) -o $(PROGRAM_NAME)
	./$(PROGRAM_NAME) test2

clean:
	rm -f $(PROGRAM_NAME) *.o