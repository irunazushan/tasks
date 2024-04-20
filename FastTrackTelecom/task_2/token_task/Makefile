CXX = gcc -g
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17
LIBS = -lstdc++ -lpthread -lm 

.PHONY: all main

all: clean main

main:
	$(CXX) $(CXXFLAGS) main.cc -o main $(LIBS)
	./main

valg:
	valgrind --tool=memcheck --leak-check=yes ./main

clang:
	clang-format -style=Google -i *.cc *.h

clean:
	rm -rf *.o main a.out clean
