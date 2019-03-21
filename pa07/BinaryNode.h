/**
  * @file BinaryNode.h
  *
  * @brief Header file for binary node
  * @details Some of the functions that are irrelevant
  * to this assignment have been removed (and thus not implemented)
  *
  * @version 1.01
  * 		Wei Tong (13 December 2016)
  * 		Added in color to the node, as well as defining red and black specifically for the R/B tree
  *
  * @version 1.00
  * 		Wei Tong (11 November 2016)
  * 		Turned in version and initial development
  */

#ifndef _BINARY_NODE
#define _BINARY_NODE
#define red 'r'
#define black 'b'
class BinaryNode{
private:
	int item;
	BinaryNode* leftChildPtr;
	BinaryNode* rightChildPtr;
	BinaryNode* parent;
	char color;
public:
	BinaryNode();
	BinaryNode(const int& anItem);
	BinaryNode(const int& anItem, BinaryNode* leftPtr, BinaryNode* rightPtr);
	void setItem(const int& anItem);
	int getItem() const;
	bool isLeaf() const;
	BinaryNode* getLeftChildPtr() const;
	BinaryNode* getRightChildPtr() const;
	BinaryNode* getParent() const;
	void setLeftChildPtr(BinaryNode* leftPtr);
	void setRightChildPtr(BinaryNode* rightPtr);
	void setParentPtr(BinaryNode* parentPtr);
	char getColor() const;
	void setColor(char newColor);
};

#endif