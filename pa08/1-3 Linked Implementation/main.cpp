/**
@file main.cpp

@brief Test driver for graph matrix linked list implementation
@details Main file for project. Will create a matrix, which
is actually a vector of lists of nodes. This driver tests
both directed and undirected, and can be switched by changing
isDirected to either true or false. This also tests the number of
vertices on a completed graph, and then removes the last connection
to show that the number of vertices didn't change, but the number of
edges did. Both depth first and breadth first search are performed, and
the numbers are output to file as they are visited. Whether the
graph is weighted or not depends on input when adding. If the
third parameter is detected, it will set that as the weight. Otherwise,
it will default to 0. Problems 1-3 of the optional project have
been completed (pg. 663 of the textbook)

@version 1.00
	Wei Tong (19 December 2016)
	Turned in version and initial development

@note
		Adapted from Frank M. Carrano and Timothy M. Henry
		Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
*/
#include "graphMatrix.h"
#include <fstream>
#define isDirected false

ofstream fout;

/**
Outputs what number was visited as the graph is traversed.
@param data An integer variable that will receive the data to be output
@pre Node in the grpah has been traversed to
@post Data in the node has been outputted
@return void
*/
void visit(int& data){
	fout << "Visited: " << data << endl;
}

int main(){
	fout.open("linked.txt");
	graphMatrix first(6, isDirected); // First parameter is how many items, second should not be changed.

	first.add(1, 3, 5000); // Example of a weighted edge addition
	first.add(3, 5); // Example of a non-weighted edge addition
	first.add(1, 2);
	first.add(2, 4);
	first.add(4, 5);
	first.add(0, 4); // This one should not show up if directed is true
	fout << "Number of vertices: " << first.getNumVertices() << endl << "Number of edges: " << first.getNumEdges() << endl;

	first.remove(3, 5); // Example of edge removal
	fout << "Number of vertices: " << first.getNumVertices() << endl << "Number of edges: " << first.getNumEdges() << endl;

	first.clearVisited(); // Clears the various data from previous traversal visitings
	fout << "Depth search--------------------" << endl;
	first.DFS(1, visit);

	first.clearVisited();
	fout << "Breadth search--------------------" << endl;
	first.BFS(1, visit);

	fout << "Edge weight between 1 and 3 is: " << first.getEdgeWeight(1, 3) << endl;

	return 0;
}