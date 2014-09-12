# Compiler
CC = g++ --std=c++11

default: clean spam

all: clean spam test

travis: clean test
	./memory/test
	./skeleton/test
	./stack/test

test: test-memory test-skeleton test-accumulator test-stack

spam:
	$(CC) skeleton/skeleton.cpp -o spam

test-memory:
	$(CC) memory/test.cpp memory/memory.cpp -o memory/test

test-skeleton:
	$(CC) -D TEST skeleton/test_skeleton.cpp skeleton/skeleton.cpp -o skeleton/test

test-accumulator:
	$(CC) -D TEST accumulator/test_accumulator.cpp -o accumulator/test

test-stack:
	$(CC) -D TEST stack/test.cpp stack/stack.cpp memory/memory.cpp -o stack/test

clean:
	rm -Rf *.o spam test */test
