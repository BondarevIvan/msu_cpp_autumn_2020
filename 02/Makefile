CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: parser

parser: test.cpp parser.cpp
	$(CC) $(FLAGS) test.cpp parser.cpp -o parser

clean:
	rm parser

test:
	make; ./parser; make clean