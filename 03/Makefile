CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: matrix

matrix: test.cpp matrix.cpp
	$(CC) $(FLAGS) test.cpp matrix.cpp -o matrix

clean:
	rm matrix

test:
	@echo "run 'make' before 'make test'"; ./matrix; rm matrix