/**
@file node.h
@brief Header file for a simple node
@details This class is extremely simple, and
doesn't contain pointers and such because I had
only needed a container that could container a
data value and the next number the current number pointed to
@version 1.00
	Wei Tong (19 December 2016)
	Turned in version and initial development
*/
struct Node{
public:
	int pointTo, weight;
};