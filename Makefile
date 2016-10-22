CFLAGS=-std=c99 -Wall -pedantic -g
BIN=project
CC=gcc
RM=rm -f

ALL: main.o garbage.o scanner.o parser.o
	$(CC) $(CFLAGS) -o $(BIN) main.o garbage.o scanner.o parser.o

clean:
	$(RM) *.o $(BIN)
