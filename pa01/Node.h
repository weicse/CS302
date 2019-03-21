/**
  * @file Node.h
  *
  * @brief Header file for Node creation
  *
  * @details Creates function prototype for the Nodes used in the linked list
  *
  * @version 1.00
  *			Wei Tong (15 September 2016)
  *			Initial development of the Node class
  *
  * @note
  *   Adapted from Frank M. Carrano and Timothy M. Henry
  *   Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */
#ifndef _NODE
#define _NODE

template<class ItemType>
class Node{
private:
	ItemType item; // A data item
	Node<ItemType>* next; // Pointer to next node
public:
  /** Default constructor for the Node class
  * @post Node class object is created
  */
	Node();

  /** Constructor for the Node class (with entry as parameter input)
  * @post Contents of Node are copied from node parameter
  */
	Node(const ItemType& anItem);

  /** Constructor for the Node class (with entry and pointer to next Node as parameter input)
  * @post Contents of Node are copied from parameter node, including next pointer.
  */
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);

  /** Set item in node to input
  * @post item in node has been set to input
  */
	void setItem(const ItemType& anItem);

  /** Set the next pointer
  * @post next pointer now set to parameter input pointer
  */
	void setNext(Node<ItemType>* nextNodePtr);

  /** Retrieve the data in the node
  * @return the data item was storing
  */
	ItemType getItem() const ;

  /** Find the node the next pointer is pointing at
  * @return A pointer pointing to the next node
  */
	Node<ItemType>* getNext() const ;
}; // end Node

#endif