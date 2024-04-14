CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17
LIBS = -lstdc++ -lpthread -lm 

.PHONY: all main

all: clean test

main:
	$(CXX) $(CXXFLAGS) main.cc -o main $(LIBS)
	./main

valg:
	valgrind --tool=memcheck --leak-check=yes ./main

clang:
	clang-format -style=Google -i *.cc

clean:
	rm -rf *.o main clean