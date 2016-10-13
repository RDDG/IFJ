CFLAGS=-std=c99 -Wall -pedantic -g
BIN=project
CC=gcc
RM=rm -f

ALL: gcmain.o garbage.o
	$(CC) $(CFLAGS) -o $(BIN) gcmain.o garbage.o

clean:
	$(RM) *.o $(BIN)