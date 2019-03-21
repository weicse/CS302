#include "Node.h"
#include <cstddef>

/*
Default constructor for the class
*/
Node::Node() : next(NULL){}

/*
Constructor with an item as a parameter
@param anItem data to be stored in the Node
*/
Node::Node(const int& anItem) : item(anItem), next(NULL){}

/*
Full constructor with next and item
@param anItem data to be stored in the Node
@param nextNodePtr The next node the node will point towards
*/
Node::Node(const int& anItem, Node* nextNodePtr) : item(anItem), next(nextNodePtr){}

/*
Sets an item in the node
@param anItem the data to be stored inside the node
*/
void Node::setItem(const int& anItem){
	item = anItem;
}

/*
Sets the next node to point to
@param nextNodePtr The next node to point to in the queue
*/
void Node::setNext(Node* nextNodePtr){
	next = nextNodePtr;
}

/*
Returns the item inside the node
@return the data in the node
*/
int Node::getItem() const{
	return item;
}

/*
Get the next node being pointed to
@return Next node in the queue
*/
Node* Node::getNext() const{
	return next;
}