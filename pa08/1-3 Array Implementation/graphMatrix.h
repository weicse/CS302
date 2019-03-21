/**
@file graphMatrix.h
@brief Header file for graph
@details The header file includes the using namespace
standard because it was required for parts of the implementation
file as well as the main, so it might as well have been put here.

@version 1.00
	Wei Tong (19 December 2016)
	Turned in version and initial development
*/
#include <iostream>
#include <deque>
using namespace std;

class graphMatrix{
private:
	int size, numEdges = 0;
	int **data;
	bool isDirected;
	deque<int> visited, BFSQ, numVertices;
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