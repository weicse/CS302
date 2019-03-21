/**
  * @file BinaryNode.h
  *
  * @brief Header file for binary node
  * @details Some of the functions that are irrelevant
  * to this assignment have been removed (and thus not implemented)
  *
  * @version 1.00
  * 		Wei Tong (11 November 2016)
  * 		Turned in version and initial development
  */

#ifndef _BINARY_NODE
#define _BINARY_NODE

class BinaryNode{
private:
	int item;
	BinaryNode* leftChildPtr;
	BinaryNode* rightChildPtr;
public:
	BinaryNode();
	BinaryNode(const int& anItem);
	BinaryNode(const int& anItem, BinaryNode* leftPtr, BinaryNode* rightPtr);
	void setItem(const int& anItem);
	int getItem() const;
	bool isLeaf() const;
	BinaryNode* getLeftChildPtr() const;
	BinaryNode* getRightChildPtr() const;
	void setLeftChildPtr(BinaryNode* leftPtr);
	void setRightChildPtr(BinaryNode* rightPtr);
};

#endif