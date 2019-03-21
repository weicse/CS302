/**
  * @file BinarySearchTree.cpp
  *
  * @brief Implementation file for binary node
  * @details Some of the functions that are irrelevant
  * to this assignment have been removed (and thus not implemented)
  *
  * @version 1.00
  * 		Wei Tong (11 November 2016)
  * 		Turned in version and initial development
  */

#include "BinarySearchTree.h"
#include <algorithm>

/** Default constructor for binary search tree
  */
BinarySearchTree::BinarySearchTree(){}

/** Fully parameterized constructor for binary search tree
  *
  * @param rootItem the first item to be added to the tree
  */
BinarySearchTree::BinarySearchTree(const int& rootItem){
	rootPtr = new BinaryNode(rootItem, nullptr, nullptr);
}

/** Sends the (sub)tree to oblivion
  *
  * @post everything under the under is deleted
  *
  * @param subTreePtr Node to start deleting from
  */
void BinarySearchTree::destroyTree(BinaryNode* subTreePtr){
	if(subTreePtr != nullptr){
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
		rootPtr = nullptr;
	}
}

/** Deconstructor
  *
  * @post Entire tree is deleted
  */
BinarySearchTree::~BinarySearchTree(){
	destroyTree(rootPtr);
}

/** Find the height of the tree recursively
  *
  * @param subTreePtr Node to start counting from
  *
  * @return The height of the tree
  */
int BinarySearchTree::getHeightHelper(BinaryNode* subTreePtr) const{
	if(subTreePtr == nullptr){
		return 0;
	}
	else{
		return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
	} // Returns 1 (the current level) plus any levels below it
}

/** Interface for finding the height
  *
  * @return the height of the tree found by
  * the called upon recursive function
  */
int BinarySearchTree::getHeight() const{
	return getHeightHelper(rootPtr);
}

/** Finds the number of nodes recursively
  *
  * @param subTreePtr Node to start counting from
  *
  * @return The number of nodes in the tree
  */
int BinarySearchTree::getNumberOfNodesHelper(BinaryNode* subTreePtr) const{
	if(subTreePtr == nullptr)
		return 0;
	else
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
	// Returns 1 (the current node) plus any nodes below it
}

/** Interface for finding the amount of nodes
  *
  * @return the number of nodes found by the
  * called upon recursive function
  */
int BinarySearchTree::getNumberOfNodes() const{
	return getNumberOfNodesHelper(rootPtr);
}

/** Inserts a new node into the tree in order
  *
  * @post node is inserted into the tree based on value
  *
  * @param subTreePtr the current node to compare value with
  * @param newNodePtr the new node to be inserted
  *
  * @return the node where the new node was inserted at
  */
BinaryNode* BinarySearchTree::insertInorder(BinaryNode* subTreePtr, BinaryNode* newNodePtr){
	if(subTreePtr == nullptr){
		return newNodePtr;
	}
	else if(newNodePtr->getItem() > subTreePtr->getItem()){
		subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(), newNodePtr));
		subTreePtr->getRightChildPtr()->setParentPtr(subTreePtr);
		/*
		BinaryNode* tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
		subTreePtr->setRightChildPtr(tempPtr);
		tempPtr->setParentPtr(subTreePtr);
		*/
	}
	else{
		subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr));
		subTreePtr->getLeftChildPtr()->setParentPtr(subTreePtr);
		/*
		BinaryNode* tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
		subTreePtr->setLeftChildPtr(tempPtr);
		tempPtr->setParentPtr(subTreePtr);
		*/
	}

	return subTreePtr;
}

/** Interface for adding a new data element into the tree
  *
  * @post specified data is entered into the tree
  *
  * @param newData data to be put into the tree
  *
  * @return if the insertion was successful (always true here)
  */
bool BinarySearchTree::add(const int& newData){
	BinaryNode* newNodePtr = new BinaryNode(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);

	fixUp(rootPtr, newNodePtr);

	return true;
}

/** Rotates the tree left at the current node
  *
  * @post tree is rotated
  *
  * @param root The root pointer of the tree
  * @param ptr The pointer to the node to be rotated
  */
void BinarySearchTree::leftRotate(BinaryNode* &root, BinaryNode* ptr){
	if(ptr->getRightChildPtr() == NULL){
		return;
	}
	else{
		BinaryNode* y = ptr->getRightChildPtr();
		if(y->getLeftChildPtr() != NULL){
			ptr->setRightChildPtr(y->getLeftChildPtr());
			y->getLeftChildPtr()->setParentPtr(ptr);
		}
		else{
			ptr->setRightChildPtr(NULL);
		}
		if(ptr->getParent() != NULL){
			y->setParentPtr(ptr->getParent());
		}
		if(ptr->getParent() == NULL){
			root = y;
		}
		else{
			if(ptr == ptr->getParent()->getLeftChildPtr()){
				ptr->getParent()->setLeftChildPtr(y);
			}
			else{
				ptr->getParent()->setRightChildPtr(y);
			}
		}
		y->setLeftChildPtr(ptr);
		ptr->setParentPtr(y);
	}
}

/** Rotates the tree right at the current node
  *
  * @post tree is rotated
  *
  * @param root The root pointer of the tree
  * @param ptr The pointer to the node to be rotated
  */
void BinarySearchTree::rightRotate(BinaryNode* &root, BinaryNode* ptr){
  if(ptr->getLeftChildPtr() == NULL){
    return;
  }
  else{
    BinaryNode* y = ptr->getLeftChildPtr();
    if(y->getRightChildPtr() != NULL){
      ptr->setLeftChildPtr(y->getRightChildPtr());
      y->getRightChildPtr()->setParentPtr(ptr);
    }
    else{
      ptr->setLeftChildPtr(NULL);
    }
    if(ptr->getParent() != NULL){
      y->setParentPtr(ptr->getParent());
    }
    if(ptr->getParent() == NULL){
      root = y;
    }
    else{
      if(ptr == ptr->getParent()->getLeftChildPtr()){
        ptr->getParent()->setLeftChildPtr(y);
      }
      else{
        ptr->getParent()->setRightChildPtr(y);
      }
    }
    y->setRightChildPtr(ptr);
    ptr->setParentPtr(y);
  }
}

/** Fix the tree after adding in a new element, rotations and colors
  *
  * @post New element is added to the tree, and the tree is balanced again
  *
  * @param root The root pointer of the tree
  * @param ptr The pointer to the node that was just added to the tree
  */
void BinarySearchTree::fixUp(BinaryNode* &root, BinaryNode* ptr){
	BinaryNode* unclePtr;
	if(root == ptr){ // When root is the pointer, set it to black and immediately return
		ptr->setColor(black);
		return;
	}
	while(ptr->getParent() != NULL && ptr->getParent()->getColor() == red){
		BinaryNode* grandpaPtr = ptr->getParent()->getParent();
		if(grandpaPtr->getLeftChildPtr() == ptr->getParent()){ // When parent is a left child
			if(grandpaPtr->getRightChildPtr() != NULL){ // When uncle exists
				unclePtr = grandpaPtr->getRightChildPtr();
				if(unclePtr->getColor() == red){ // Set uncle and parent to black, grandparent to red
					ptr->getParent()->setColor(black);
					unclePtr->setColor(black);
					grandpaPtr->setColor(red);
					ptr = grandpaPtr;
				}
				else{ // Uncle is not red
					if(grandpaPtr == root){ // When grandparent is root
						root = ptr->getParent();
						ptr->getParent()->setParentPtr(NULL);
						grandpaPtr->setLeftChildPtr(ptr->getParent()->getRightChildPtr());
						if(grandpaPtr->getLeftChildPtr() != NULL){
							grandpaPtr->getLeftChildPtr()->setParentPtr(grandpaPtr);
						}
						ptr->getParent()->setRightChildPtr(grandpaPtr);
						grandpaPtr->setParentPtr(ptr->getParent());
						grandpaPtr->setColor(red);
					}
					else{ // Custom rotation
						ptr->getParent()->setRightChildPtr(ptr->getLeftChildPtr());
						if(ptr->getParent()->getRightChildPtr() != NULL){
							ptr->getParent()->getRightChildPtr()->setParentPtr(ptr->getParent());
						}
						grandpaPtr->setLeftChildPtr(ptr);
						ptr->setLeftChildPtr(ptr->getParent());
						ptr->setParentPtr(grandpaPtr);
						ptr->getLeftChildPtr()->setParentPtr(ptr);
						ptr = ptr->getLeftChildPtr();
					}
				}
			}
			else{ // Uncle does not exist
				if(ptr->getParent()->getRightChildPtr() == ptr){
					ptr = ptr->getParent();
					leftRotate(root, ptr);
				}
				ptr->getParent()->setColor(black);
				grandpaPtr->setColor(red);
				rightRotate(root, grandpaPtr);
			}
		}
		else{ // When parent is a right child. Same as above, except when parent is right child instead
			if(grandpaPtr->getLeftChildPtr() != NULL){
				unclePtr = grandpaPtr->getLeftChildPtr();
				if(unclePtr->getColor() == red){
					ptr->getParent()->setColor(black);
					unclePtr->setColor(black);
					grandpaPtr->setColor(red);
					ptr = grandpaPtr;
				}
				else{
					if(grandpaPtr == root){
						root = ptr->getParent();
						ptr->getParent()->setParentPtr(NULL);
						grandpaPtr->setRightChildPtr(ptr->getParent()->getLeftChildPtr());
						if(grandpaPtr->getRightChildPtr() != NULL){
							grandpaPtr->getRightChildPtr()->setParentPtr(grandpaPtr);
						}
						ptr->getParent()->setLeftChildPtr(grandpaPtr);
						grandpaPtr->setParentPtr(ptr->getParent());
						grandpaPtr->setColor(red);
					}
					else{
						ptr->getParent()->setLeftChildPtr(ptr->getRightChildPtr());
						if(ptr->getParent()->getLeftChildPtr() != NULL){
							ptr->getParent()->getLeftChildPtr()->setParentPtr(ptr->getParent());
						}
						grandpaPtr->setRightChildPtr(ptr);
						ptr->setRightChildPtr(ptr->getParent());
						ptr->setParentPtr(grandpaPtr);
						ptr->getRightChildPtr()->setParentPtr(ptr);
						ptr = ptr->getRightChildPtr();
					}
				}
			}
			else{
				if(ptr->getParent()->getLeftChildPtr() == ptr){
					ptr = ptr->getParent();
					rightRotate(root, ptr);
				}
				ptr->getParent()->setColor(black);
				grandpaPtr->setColor(red);
				leftRotate(root, grandpaPtr);
			}
		}
		root->setColor(black); // Set root to black because it might have changed
	}
}


/** Visits the nodes in preorder, starting from specified node
  *
  * @param visit Function to do things when visiting the node
  * @param treePtr Node to start visitng from
  */
void BinarySearchTree::preorder(void visit(int&), BinaryNode* treePtr) const{
	if(treePtr != nullptr){
		int theItem = treePtr->getItem();
		visit(theItem); // Visit top element
		preorder(visit, treePtr->getLeftChildPtr()); // visit left branch
		preorder(visit, treePtr->getRightChildPtr()); // visit right brance
	}
}

/** Visits the nodes in order by value, starting from specified node
  *
  * @param visit Function to do things when visiting the node
  * @param treePtr Node to start visitng from
  */
void BinarySearchTree::inorder(void visit(int&), BinaryNode* treePtr) const{
	if(treePtr != nullptr){
		inorder(visit, treePtr->getLeftChildPtr());
		int theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	}
}

/** Visits the nodes in post order, starting from specified node
  *
  * @param visit Function to do things when visiting the node
  * @param treePtr Node to start visitng from
  */
void BinarySearchTree::postorder(void visit(int&), BinaryNode* treePtr) const{
	if(treePtr != nullptr){
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		int theItem = treePtr->getItem();
		visit(theItem);
	}
}

/** Interface for visiting the tree in preorder
  *
  * @param visit Function to do things when visiting the node
  */
void BinarySearchTree::preorderTraverse(void visit(int&)) const{
	preorder(visit, rootPtr);
}

/** Interface for visiting the tree in order
  *
  * @param visit Function to do things when visiting the node
  */
void BinarySearchTree::inorderTraverse(void visit(int&)) const{
	inorder(visit, rootPtr);
}

/** Interface for visiting the tree in pstorder
  *
  * @param visit Function to do things when visiting the node
  */
void BinarySearchTree::postorderTraverse(void visit(int&)) const{
	postorder(visit, rootPtr);
}

/** Check whether the tree is empty or not
  *
  * @return whether rootPtr points to null (empty)
  */
bool BinarySearchTree::isEmpty() const{
	return rootPtr == nullptr;
}

/** Remove a node
  *
  * @post the specified node is removed, and the rest of the
  * tree is shifted accordingly
  *
  * @param nodePtr the node to be removed
  *
  * @return a pointer to the new node in the position
  */
BinaryNode* BinarySearchTree::removeNode(BinaryNode* nodePtr){
	if(nodePtr->isLeaf() == true){ // If the node has no children
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	else if((nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr) || (nodePtr->getRightChildPtr() == nullptr && nodePtr->getLeftChildPtr() != nullptr)){
		// If the tree has one child
		BinaryNode* nodeToConnectPtr;
		if(nodePtr->getLeftChildPtr() != nullptr){ // If the subtree only has a left child
			nodeToConnectPtr = nodePtr->getLeftChildPtr();
		}
		else{ // If subtree has right child
			nodeToConnectPtr = nodePtr->getRightChildPtr();
		}
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else{
		// If the tree has two children
		// This will find the smallest value on the right branch
		int inorderSuccessor;
		BinaryNode* tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), inorderSuccessor);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setItem(inorderSuccessor);
		return nodePtr;
	}
}

/** Remove a certain value from the tree
  *
  * @param subTreePtr current node to start searching from
  * @param target the number to be removed
  * @param success if the operation has succeeded
  *
  * @return a null pointer if no value was removed, or the pointer to the node
  * that replaced the old node's position after correctly shifting the tree
  */
BinaryNode* BinarySearchTree::removeValue(BinaryNode* subTreePtr, const int target, bool& success){
	if(subTreePtr == nullptr){ // Value not in tree
		success = false;
		return nullptr;
	}
	else if(subTreePtr->getItem() == target){ // Value found
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else if(subTreePtr->getItem() > target){ // Value is greater than current node
		BinaryNode* tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
	else{ // Value is less than current node
		BinaryNode* tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;
	}
}

/** Interface for removing a number from the tree
  *
  * @param data integer to be removed from the tree
  *
  * @return a bool signalling whether the operation was successful
  */
bool BinarySearchTree::remove(const int& data){
	bool success = false;
	rootPtr = removeValue(rootPtr, data, success);
	return success;
}

/** Removes everything in the tree
  *
  * @post entirety of tree's contents have been removed
  */
void BinarySearchTree::clear(){
	destroyTree(rootPtr);
}

/** Removes the smalles value of the (sub)tree
  *
  * @param subTreePtr current node to start searching from
  * @param inorderSuccessor integer to store the value of the node
  *
  * @return the node that was removed at the leftmost side of the tree
  */
BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* subTreePtr, int& inorderSuccessor) {
    if(subTreePtr->getLeftChildPtr() == nullptr) { // End of the line, current node is smallest
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else {
        subTreePtr->setLeftChildPtr(removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor));
        return subTreePtr;

    }
}