# Compiler
CC = g++

# Compiler flags
CFLAGS = -c

skeleton: skeleton.cpp
	$(CC) skeleton.cpp -o spam

all: skeleton

clean:
	rm -Rf *.o spam
