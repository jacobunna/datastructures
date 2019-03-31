CC=gcc
LINK_CFLAGS=-g3 -pedantic -Wall
CFLAGS=-ansi -g3 -pedantic -Wall

all: datastructures

datastructures: test.o ll.o
	$(CC) $(LINK_CFLAGS) -o $@ $^

test: datastructures
		./datastructures

ll.o: ll.c ll.h
test.o: test.c ll.h minunit.h

clean:
		$(RM) datastructures *.o
