CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

test : main.o BinaryNode.o BinarySearchTree.o
	$(CC) $(LFLAGS) -std=c++11 BinaryNode.o BinarySearchTree.o main.o -o test

main.o : main.cpp
	$(CC) $(CFLAGS) -std=c++11 main.cpp

BinaryNode.o : BinaryNode.h BinaryNode.cpp
	$(CC) $(CFLAGS) -std=c++11 BinaryNode.cpp

BinarySearchTree.o : BinarySearchTree.h BinarySearchTree.cpp
	$(CC) $(CFLAGS) -std=c++11 BinarySearchTree.cpp
	
clean:
	rm -rf *~ *.o test*