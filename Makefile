# Compiler
CC = g++ --std=c++11
##CC = clang --std=c++11

default: clean spam

all: clean spam test

travis: clean test
	./memory/test
	./skeleton/test
	./stack/test
	./accumulator/test
	./registry/test

test: test-memory test-skeleton test-accumulator test-stack test-registry

spam:
	$(CC) skeleton/skeleton.cpp memory/memory.cpp accumulator/accumulator.cpp stack/stack.cpp -o spam

test-memory:
	$(CC) -D TEST memory/test.cpp memory/memory.cpp -o memory/test

test-skeleton:
	$(CC) -D TEST skeleton/test.cpp skeleton/skeleton.cpp memory/memory.cpp accumulator/accumulator.cpp stack/stack.cpp -o skeleton/test

test-accumulator:
	$(CC) -D TEST accumulator/test.cpp accumulator/accumulator.cpp memory/memory.cpp -o accumulator/test

test-stack:
	$(CC) -D TEST stack/test.cpp stack/stack.cpp memory/memory.cpp -o stack/test

test-registry:
	$(CC) registry/test.cpp registry/registry.cpp -o registry/test

clean:
	rm -Rf *.o spam test */test SHIBBOLETH*
