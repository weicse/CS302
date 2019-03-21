CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

test : main.o graphMatrix.o
	$(CC) $(LFLAGS) -std=c++11 graphMatrix.o main.o -o test

main.o : main.cpp
	$(CC) $(CFLAGS) -std=c++11 main.cpp

graphMatrix.o : node.h graphMatrix.h graphMatrix.cpp
	$(CC) $(CFLAGS) -std=c++11 graphMatrix.cpp

clean:
	rm -rf *~ *.o test*