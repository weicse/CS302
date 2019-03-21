/**
  * @file BinarySearchTree.h
  *
  * @brief Header file for binary search tree
  * @details Some of the functions that are irrelevant
  * to this assignment have been removed (and thus not implemented)
  *
  * @version 1.00
  * 		Wei Tong (11 November 2016)
  * 		Turned in version and initial development
  */

#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include "BinaryNode.h"

class BinarySearchTree{
private:
	BinaryNode* rootPtr;
protected:
	int getHeightHelper(BinaryNode* subTreePtr) const;
	int getNumberOfNodesHelper(BinaryNode* subTreePtr) const;
	void destroyTree(BinaryNode* subTreePtr);
	BinaryNode* insertInorder(BinaryNode* subTreePtr, BinaryNode* newNode);
	BinaryNode* removeValue(BinaryNode* subTreePtr, const int target, bool& success);
	BinaryNode* removeNode(BinaryNode* nodePtr);
	BinaryNode* removeLeftmostNode(BinaryNode* subTreePtr, int& inorderSuccessor);
	void preorder(void visit(int&), BinaryNode* treePtr) const;
	void inorder(void visit(int&), BinaryNode* treePtr) const;
	void postorder(void visit(int&), BinaryNode* treePtr) const;
public:
	BinarySearchTree();
	BinarySearchTree(const int& rootItem);
	~BinarySearchTree();
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	bool add(const int& newData);
	bool remove(const int& data);
	void clear();

	void preorderTraverse(void visit(int&)) const;
	void inorderTraverse(void visit(int&)) const;
	void postorderTraverse(void visit(int&)) const;
};

#endif