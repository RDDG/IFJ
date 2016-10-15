CFLAGS=-std=c99 -Wall -pedantic -g
BIN=project
CC=gcc
RM=rm -f

ALL: main.o garbage.o scanner.o
	$(CC) $(CFLAGS) -o $(BIN) main.o garbage.o scanner.o

clean:
	$(RM) *.o $(BIN)
