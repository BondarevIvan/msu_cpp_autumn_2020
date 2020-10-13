CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: allocator

allocator: test.cpp allocator.cpp
	$(CC) $(FLAGS) test.cpp allocator.cpp -o allocator

clean:
	rm allocator