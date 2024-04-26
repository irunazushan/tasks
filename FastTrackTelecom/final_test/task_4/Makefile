CC = gcc -g
CFLAGS := -Wall -Werror -Wextra
LIBS = -lstdc++
SRC = test.cpp
OBJS = $(SRC:.cpp=.o)

.PHONY: main

all: clean main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

main: clean
	$(CC) $(CFLAGS) main.cpp $(LIBS)
	./a.out

clang:
	clang-format -i -style=Google *.cpp

clean:
	rm -rf *.o test test.a main a.out