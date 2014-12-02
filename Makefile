# Compiler
CC = g++ --std=c++11
CCT = g++ --std=c++11 -D TEST
##CC = clang --std=c++11
LATCHES = pipe-gpr/latches.cpp

default: clean spam

all: clean spam test

travis: clean test
	./memory/test
	./stack/test
	./accumulator/test
	./registry/test
	./gpr/test
	./skeleton/test
	./pipe-gpr/test

test: test-memory test-accumulator test-stack test-registry test-gpr test-pipe-gpr test-skeleton

spam:
	$(CC) skeleton/skeleton.cpp memory/memory.cpp registry/registry.cpp accumulator/accumulator.cpp stack/stack.cpp gpr/gpr.cpp pipe-gpr/pipe-gpr.cpp $(LATCHES) -g -o spam

test-memory:
	$(CCT) memory/test.cpp memory/memory.cpp -o memory/test

test-accumulator:
	$(CCT) accumulator/test.cpp accumulator/accumulator.cpp memory/memory.cpp -o accumulator/test

test-stack:
	$(CCT) stack/test.cpp stack/stack.cpp memory/memory.cpp -o stack/test

test-gpr:
	$(CCT) gpr/test.cpp gpr/gpr.cpp memory/memory.cpp registry/registry.cpp -o gpr/test

test-pipe-gpr:
	$(CCT) pipe-gpr/test.cpp pipe-gpr/pipe-gpr.cpp $(LATCHES) memory/memory.cpp registry/registry.cpp -o pipe-gpr/test

test-registry:
	$(CCT) registry/test.cpp registry/registry.cpp -o registry/test

test-skeleton:
	$(CCT) skeleton/test.cpp skeleton/skeleton.cpp memory/memory.cpp registry/registry.cpp accumulator/accumulator.cpp stack/stack.cpp gpr/gpr.cpp pipe-gpr/pipe-gpr.cpp $(LATCHES) -o skeleton/test

clean:
	rm -Rf *.o spam test */test SHIBBOLETH*
