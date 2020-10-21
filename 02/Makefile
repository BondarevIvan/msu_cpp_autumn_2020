CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: parser

parser: test.cpp parser.cpp
	$(CC) $(FLAGS) test.cpp parser.cpp -o parser

clean:
	rm parser

test:
	@echo "run 'make' before 'make test'"; ./parser; rm parser