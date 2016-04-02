CC = g++
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -g -Wall -Wextra -I/usr/local/lib -L/usr/local/lib -lsndfile

.PHONY: all clean

all: test

test: w2b.o test.cpp
	$(CC) $(LFLAGS) $^ -o $@

w2b.o: lib/w2b.cpp lib/w2b.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f *~
