/**
@file graphMatrix.cpp
@brief Implementation file for the graph
@details I was not sure how to implement the infinity in
the case that two vertices were not connected, so I set it
to the maximum an integer could be on a 64-bit machine.
@version 1.00
	Wei Tong (19 December 2016)
	Turned in version and initial development
*/
#include "graphMatrix.h"
#include <algorithm>
#define INVALID_NUM 2147483647

/**
Fully parameterized constructor for the graph.
@param num The number of possible elements (vertices) in the graph
@param direc Whether the graph is directed or not
@post The graph is created and initialized to infinity (INVALID_NUM)
*/
graphMatrix::graphMatrix(int num, bool direc){
	size = num;
	isDirected = direc;
	data = new int*[num];
	for(int i = 0; i < num; i++){
		data[i] = new int[num];
	} // Create arrays within the array

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			data[i][j] = INVALID_NUM;
		}
	} // Set all to infinity
}

/**
Deconstructor for the graph class.
@pre Graph object has dynamically allocated data
@post All dynamically allocated data in the object is freed
*/
graphMatrix::~graphMatrix(){
	for(int i = 0; i < size; i++){
		delete[] data[i];
	}
	delete[] data;
}

/**
Function to find the number of vertices in the graph
@pre number of vertices is unknown
@post The number of vertices is known
@ return The size of the deque containing a list of unique vertices
*/
int graphMatrix::getNumVertices() const{
	return numVertices.size();
}

/**
Function to find the number of edges in the graph
@pre The number of vertices is unknown
@post The number of vertices is known
@return The integer representing the number of edges in the graph
*/
int graphMatrix::getNumEdges() const{
	return numEdges;
}

/**
Function to find the weight of the edge between two vertices
@pre Two vertices are given, and the edge between them unknown
@post The weight of the edge between two given vertices is known
@param start The starting vertex of the edge to be weighed
@param end The ending vertex of the edge to be weighed
@return The value of the data in the 2d graph at the specified coordinates
*/
int graphMatrix::getEdgeWeight(int start, int end) const{
	return data[start][end];
}

/**
Function to add an edge between two vertices. If an edge already exists, it will
not be created and false will be returned. If the edge was successfully created, the
function will check whether or not the two vertices are in the list of existing vertices,
and add them to the list if necessary. If the graph is not directed, the reversed
coordinates will also have the same edge added to them
@pre Two vertices are given, regardless of existing edges
@post An edge is created between the two vertices if there isn't one already
@param start The vertex the edge should start at
@param end The vertex the edge should end at
@param edgeWeight The weight of the to-be edge
@return Whether or not a new edge was created
*/
bool graphMatrix::add(int start, int end, int edgeWeight){
	if(data[start][end] == INVALID_NUM){
		numEdges += 1; // Keep track of the number of edges
		data[start][end] = edgeWeight; // Set the weight of the edge
		if(!isDirected)
			data[end][start] = edgeWeight;	// Set the other edge weight if not directed
		if(find(numVertices.begin(), numVertices.end(), start) == numVertices.end()){ // Check if vertex exists and is unique
			numVertices.push_back(start); // Add vertex to list of vertices with an edge
		}
		if(find(numVertices.begin(), numVertices.end(), end) == numVertices.end()){ // Check if vertex exists and is unique
			numVertices.push_back(end);
		}
		return true;
	}
	else{
		return false;
	}
}

/**
Function to remove an edge between two vertices. If the edge does not exist, the function
will return false. If it does exist, the integer representing the number of edges is
decremented. If the graph is not directed, the other coordinate (reversed start and end)
will also be removed. The function then checks if anything is connected to the two vertices
and will remove them from the list of used and unique vertices if they are not.
@pre Two vertices are given, regardless of existing edges
@post An edge is removed if one exists
@param start The vertex the edge starts from
@param end The vertex the edge ends at
@return Returns whether or not an existing edge was removed
*/
bool graphMatrix::remove(int start, int end){
	bool exist;
	if(data[start][end] != INVALID_NUM){
		numEdges -=1;
		data[start][end] = INVALID_NUM;
		if(!isDirected)
			data[end][start] = INVALID_NUM;	// Directionless
		
		exist = false;
		for(int i = 0; i < size; i++){ // Check if start is connected to anything
			if(data[start][i] != INVALID_NUM)
				exist = true;
			if(data[i][start] != INVALID_NUM)
				exist = true;
		}
		if(!exist){ // Remove start from list of vertices
			for(int i = 0; i < (int)numVertices.size(); i++){
				if(start == numVertices.at(i)){
					numVertices.erase(numVertices.begin() + i);
				}
			}
		}
		exist = false;
		for(int i = 0; i < size; i++){ // Check if end is connected to anything
			if(data[i][end] != INVALID_NUM)
				exist = true;
			if(data[end][i] != INVALID_NUM)
				exist = true;
		}
		if(!exist){ // Remove end from list of vertices
			for(int i = 0; i < (int)numVertices.size(); i++){
				if(end == numVertices.at(i)){
					numVertices.erase(numVertices.begin() + i);
				}
			}
		}
		
		return true;
	}
	else{
		return false;
	}
}
/**
Function to traverse through the graph using a depth first approach. The number
being visited is pushed to the front of a deque outside of the function, because
the function is recursive. The number being visited is then sent to the visit function,
which can do various things such as outputting the data value. For each vertex
adjacent to the currently visited function will then be visited using this same
function, which effectively visits all of the connected vertices depth first. All
the adjacent vertices will be visited in order from smallest to largest, by virtue
of the 2d array/matrix being ordered numberically (think of it like coordinate plane).
@pre The "visited" deque should have been emptied beforehand
@post The "visited" deque should not be empty, and the graph has been traversed in a depth first approach.
@param start The vertex to start the iteration of DFS from
@param visit The function to do stuff like outputting the data value
*/
void graphMatrix::DFS(int start, void visit(int&)){
	visited.push_front(start);
	visit(start);
	for(int i = 0; i < size; i++){
		if(i != start && data[start][i] != INVALID_NUM && find(visited.begin(), visited.end(), i) == visited.end()){
			DFS(i, visit);
		}
	}
}

/**
Function to traverse through the graph using a breadth first approach. The number
being visited is pushed to the front of a deque outside of the function, because
it can also be used by the recursive depth first approach. The number is then sent
to another deque, BFSQ which is the deque of numbers to be visited next. The number
is then sent to the visit function, to do various activities such as outputting the data.
The entire list of numbers are then visited at that specific number (horizontally in a matrix).
If the number doesn't match with current number being visited, has an edge, and is not
in the visited deque, it is added to the visited deque and BFSQ deque.
@pre The "visited" and "BFSQ" deque should have been emptied beforehand
@post The graph has been traversed in a breadth first approach
@param start The vertex to start the breadth first traversal from
@param visit The function to do stuff like outputting data values
*/
void graphMatrix::BFS(int start, void visit(int&)){
	visited.push_front(start);
	BFSQ.push_back(start);
	while(!BFSQ.empty()){
		start = BFSQ.front();
		BFSQ.pop_front();
		visit(start);
		for(int i = 0; i < size; i++){
			if(i != start && data[start][i] != INVALID_NUM && find(visited.begin(), visited.end(), i) == visited.end()){
				visited.push_front(i);
				BFSQ.push_back(i);
			}
		}
	}
}

/**
Function to clear the deques that may have been used before hand. These deques are
important because they help keep track of whats been visited, thus needing
to be emptied before being used again in another traversal.
@pre The "visited" and "BFSQ" deques may not be emptied
@post The two deques have been emptied
*/
void graphMatrix::clearVisited(){
	visited.clear();
	BFSQ.clear();
}