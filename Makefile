CFLAGS=-std=c99 -Wall -pedantic -g
BIN=project
CC=gcc
RM=rm -f

ALL: main.o
	$(CC) $(CFLAGS) -o $(BIN) main.o

clean:
	$(RM) *.o $(BIN)
