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
@post The graph is created by filling the vector with the specified number of lists
*/
graphMatrix::graphMatrix(int num, bool direc){
	isDirected = direc;
	list<Node> tmp; // Created outside loop. Is empty so it can be push_back multiple times
	for(int i = 0; i < num; i++){
		data.push_back(tmp);
	} // Pushed an empty list several times into the vector
	size = num;
}

/**
Deconstructor for the graph class.
@pre Graph object has dynamically allocated data
@post All dynamically allocated data in the object is freed
*/
graphMatrix::~graphMatrix(){
	for(int i = 0; i < size; i++){
		data[i].clear();
	}
	data.clear();
}

/**
Function to find the number of vertices in the graph. If the graph
is not directed, it is relatively straightforward. However, if it is
not, a temporary deque is created to store the unique, connected 
vertice numbers.
@pre number of vertices is unknown
@post The number of vertices is known
@ return The number of vertices in the current graph
*/
int graphMatrix::getNumVertices() const{
	int num = 0;
	if(!isDirected){
		for(int i = 0; i < size; i++){
			if(!data[i].empty()){
				num++;
			}
		}
	} // This works when the graph is undirected.
	else{
		deque<int> tmp; // Create a temporary deque to store unique vertices
		for(int i = 0; i < size; i++){ // Go through every list in the vector
			if(!data[i].empty()){ // Go through every node in the list
				if(find(tmp.begin(), tmp.end(), i) == tmp.end()){
					tmp.push_back(i); // Put the "start" vertex into tmp
				}
				list<Node>::const_iterator ptr = data[i].begin();
				while(ptr != data[i].end()){
					if(find(tmp.begin(), tmp.end(), ptr->pointTo) == tmp.end()){
						tmp.push_back(ptr->pointTo);
					} // Found unique vector, push to tmp
					ptr++;
				}
			}
		}
		num = tmp.size();
	}
	return num;
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
	for(list<Node>::const_iterator ptr = data[start].begin(); ptr != data[start].end(); ptr++){
		if(ptr->pointTo == end){
			return ptr->weight;
		}
	}
	return INVALID_NUM;
}

/**
Function to add an edge between two vertices. If an edge is attempted to be made
from a vertex to itself, it immediately fails. If an edge already exists, it will
not be created and will fail. If the edge was successfully created, the function
will check whether or not the graph is directed, and if not create an edge from
the "end" vertex to the "start" vertex.
@pre Two vertices are given, regardless of existing edges
@post An edege is created between two unique vertices, if one doesn't exist already
@param start The vertex the edge should start at
@param end The vertex the edge should end at
@param edgeWeight The weight of the to-be edge
@return Whether or not a new edge was created
*/
bool graphMatrix::add(int start, int end, int edgeWeight){
	if(start == end){
		return false;
	}
	bool exist = false;
	for(list<Node>::const_iterator ptr = data[start].begin(); ptr != data[start].end(); ptr++){
		if(ptr->pointTo == end){
			exist = true;
		}
	}
	if(!exist){
		Node tmp;
		tmp.pointTo = end;
		tmp.weight = edgeWeight;
		data[start].push_back(tmp);
		if(!isDirected){
			tmp.pointTo = start;
			data[end].push_back(tmp);
		}
		numEdges++;
		return true;
	}
	else{
		return false;
	}
}

/**
Function to remove an edge between two vertices. If the two vertices are
indentical, the function will fail instantly. If the edge does not exist,
the function will also fail. If the graph is not directed, the reverse
coordinate will also be removed. The function then checks if anything is
connected to the two vertices, and removes them from the list of connected
and unique vertices if they are not.
@pre Two vertices are given, regardless of existing edges
@post An edge is removed if one exists
@param start The vertex the edge starts from
@param end The vertex the edge ends at
@return Returns whether or not an existing edge was removed
*/
bool graphMatrix::remove(int start, int end){
	if(start == end){
		return false;
	}
	list<Node>::iterator ptr = data[start].begin();
	while(ptr != data[start].end()){
		if(data[end].begin()->pointTo == start){
			data[end].pop_front();
		}
		else if(ptr->pointTo == end){
			ptr->pointTo = data[start].end()->pointTo;
			ptr->weight = data[start].end()->weight;
			data[start].pop_back();
			numEdges--;
			ptr = data[start].end();
		}
		else{
			ptr++;
		}
	}
	if(!isDirected){
		ptr = data[end].begin();
		while(ptr != data[end].end()){
			if(data[end].begin()->pointTo == start){
				data[end].pop_front();
			}
			else if(ptr->pointTo == start){
				ptr->pointTo = data[end].end()->pointTo;
				ptr->weight = data[end].end()->weight;
				data[end].pop_back();
				ptr = data[end].end();
			}
			else{
				ptr++;
			}
		}
	}

	return true;
}

/**
Function to traverse through the graph using a depth first approach. The number
being visited is pushed to the front of a deque outside of the function, because
the function is recursive. The number being visited is then sent to the visit function,
which can do various things such as outputting the data value. For each vertex
adjacent to the currently visited function will then be visited using this same
function, which effectively visits all the connected vertices depth first. All
the adjacent vertices will be visited in order numerically, by sending all the adjacent
nodes to a list and sorting, before dumping them back into the recursive function.
@pre The "visited" deque should have been emptied beforehand
@post The "visited" deque should not be empty, and the graph has been traversed in a depth first approach.
@param start The vertex to start the iteration of DFS from
@param visit The function to do stuff like outputting the data value
*/
void graphMatrix::DFS(int start, void visit(int&)){
	visited.push_front(start);
	visit(start);
	list<Node>::const_iterator ptr = data[start].begin();
	list<int> tmp;
	while(ptr != data[start].end()){
		if(find(visited.begin(), visited.end(), ptr->pointTo) == visited.end()){
			tmp.push_back(ptr->pointTo);
		}
		ptr++;
	}
	tmp.sort();
	while(!tmp.empty()){
		DFS(tmp.front(), visit);
		tmp.pop_front();
	}
}

/**
Function to traverse through the graph using a breadth first approach. The number
being visited is pushed to the front of a deque outside of the function, because
it can also be used by the recursive depth first approach. The number is then sent
to another deque, BFSQ which is the deque of numbers to be visited next. The number
is then sent to the visit function, to do various activities such as outputting the data.
All the adjacent vertices are then placed into a temporary deque, sorted, then dumped
into the BFSQ deque, which is outside the while function. If the number doesn't match
with the current number being visited, has an edge, and is not in the visited deque,
it is added to the visited deque and BFSQ deque, before being popped from the tmp deque.
@pre The "visited" and "BFSQ" deque should have been emptied beforehand
@post The graph has been traversed in a breadth first approach
@param start The vertex to start the breadth first traversal from
@param visit The function to do stuff like outputting data values
*/
void graphMatrix::BFS(int start, void visit(int&)){
	list<Node>::const_iterator ptr;
	visited.push_front(start);
	BFSQ.push_back(start);
	while(!BFSQ.empty()){
		start = BFSQ.front();
		BFSQ.pop_front();
		visit(start);
		ptr = data[start].begin();
		list<int> tmp;
		while(ptr != data[start].end()){
			if(find(visited.begin(), visited.end(), ptr->pointTo) == visited.end()){
				tmp.push_back(ptr->pointTo);
			}
			ptr++;
		}
		tmp.sort();
		while(!tmp.empty()){
			visited.push_front(tmp.front());
			BFSQ.push_back(tmp.front());
			tmp.pop_front();
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