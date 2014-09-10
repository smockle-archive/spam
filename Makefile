# Compiler
CC = g++

# Compiler flags
CFLAGS = -c

all: spam

spam: skeleton/skeleton.cpp
	$(CC) skeleton/skeleton.cpp -o spam

clean:
	rm -Rf *.o spam
