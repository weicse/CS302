/**
@file graphMatrix.h
@brief Header file for graph
@details The header file includes the using namespace
standard because it was required for parts of the implementation
file as well as the main, so it might as well have been put here.
Vector, list and deque were also used because they had various
properties that I could make use of. For example, vector is like
an array, but can be of stuff other than integers or characters,
so I used it to be an array of lists. std::list is a linked list that
was pre-made, so I used it thinking it would be beneficial to be able
to switch from nodes to another data type, without having to rewrite
the entire program (for future usage)

@version 1.00
	Wei Tong (19 December 2016)
	Turned in version and initial development
*/
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "node.h"
using namespace std;

class graphMatrix{
private:
	int size, numEdges = 0;
	bool isDirected;
	vector< list<Node> > data;
	deque<int> visited, BFSQ;
public:
	graphMatrix(int, bool);
	~graphMatrix();
	int getNumVertices() const;
	int getNumEdges() const;
	int getEdgeWeight(int start, int end) const;
	bool add(int start, int end, int edgeWeight = 0);
	bool remove(int start, int end);
	void DFS(int start, void visit(int&));
	void BFS(int start, void visit(int&));
	void clearVisited();
};