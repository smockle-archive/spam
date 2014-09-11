# Compiler
CC = g++ --std=c++11

default: spam

all: spam test

test: test-memory test-skeleton

spam:
	$(CC) skeleton/skeleton.cpp -o spam

test-memory:
	$(CC) memory/test.cpp memory/memory.cpp -o memory/test

test-skeleton:
	$(CC) skeleton/test_skeleton.cpp skeleton/skeleton.cpp -o skeleton/test

clean:
	rm -Rf *.o spam test */test
