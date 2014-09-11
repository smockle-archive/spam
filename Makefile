# Compiler
CC = g++

# Compiler flags
CFLAGS = -c

all: spam

spam: skeleton/skeleton.cpp
	$(CC) skeleton/skeleton.cpp -o spam

test-mem:
	$(CC) memory/test.cpp memory/memory.cpp -o memory/test

clean:
	rm -Rf *.o spam
