CC=g++
LFLAGS=-lm -lfann -lm
CFLAGS=-Wall

tester: neural-network.cpp
	$(CC) $^ -o neural-network $(LFLAGS) $(CFLAGS)

clean:
	$(RM) neural-network 
