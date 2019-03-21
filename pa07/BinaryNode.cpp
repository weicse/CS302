/**
  * @file BinaryNode.cpp
  *
  * @brief Implementation file for binary node
  * @details Some of the functions that are irrelevant
  * to this assignment have been removed (and thus not implemented)
  *
  * @version 1.00
  * 		Wei Tong (11 November 2016)
  * 		Turned in version and initial development
  */

#include "BinaryNode.h"

/** Default constructor for binary node
  */
BinaryNode::BinaryNode(){}

/** Partially parameterized constructor for binary node
  *
  * @param anItem Number to be placed inside the node
  */
BinaryNode::BinaryNode(const int& anItem){
	color = red;
	setItem(anItem);
}

/** Fully parameterized constructor for binary node
  *
  * @param anItem Number to be placed inside the node
  * @param leftPtr The node that will be placed on the left
  * side of this node
  * @param rightPtr The node that will be placed on the right
  * side of this node
  */
BinaryNode::BinaryNode(const int& anItem, BinaryNode* leftPtr, BinaryNode* rightPtr){
	color = red;
	setItem(anItem);
	setLeftChildPtr(leftPtr);
	setRightChildPtr(rightPtr);
}

/** Changes integer item to the specified integer in parameter
  *
  * @param anItem Number to be changed to
  */
void BinaryNode::setItem(const int& anItem){
	item = anItem;
}

/** Returns the number at the node
  *
  * return item stored in the node
  */
int BinaryNode::getItem() const{
	return item;
}

/** Returns if the node has no children
  *
  * @return if the node doesn't have children
  */
bool BinaryNode::isLeaf() const{
	return (getLeftChildPtr() == nullptr && getRightChildPtr() == nullptr);
}

/** Find the node's left child
  *
  * @return a pointer to the node's left child
  */
BinaryNode* BinaryNode::getLeftChildPtr() const{
	return leftChildPtr;
}

/** Find the node's right child
  *
  * @return a pointer to the node's right child
  */
BinaryNode* BinaryNode::getRightChildPtr() const{
	return rightChildPtr;
}

BinaryNode* BinaryNode::getParent() const{
	return parent;
}

/** Set the node's left child
  */
void BinaryNode::setLeftChildPtr(BinaryNode* leftPtr){
	leftChildPtr = leftPtr;
}

/** Set the node's right child
  */
void BinaryNode::setRightChildPtr(BinaryNode* rightPtr){
	rightChildPtr = rightPtr;
}

void BinaryNode::setParentPtr(BinaryNode* parentPtr){
	parent = parentPtr;
}

char BinaryNode::getColor() const{
	return color;
}

void BinaryNode::setColor(char newColor){
	color = newColor;
}