/**
  * @file Node.cpp
  *
  * @brief Implementation file for Node creation
  *
  * @details Creates function prototype for the Nodes used in the linked list
  *
  * @version 1.00
  *		Wei Tong (15 September 2016)
  *		Initial development of the Node class
  *
  * @note
  * 	Adapted from Frank M. Carrano and Timothy M. Henry
  * 	Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */
#include "Node.h"
#include <cstddef>

/** Default constructor for the Node class
  * @post Node class object is created
  */
template<class ItemType>
Node<ItemType>::Node() : next(nullptr){

} // end default constructor

/** Constructor for the Node class (with entry as parameter input)
  * @post Contents of Node are copied from node parameter
  */
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr){

} // end constructor

/** Constructor for the Node class (with entry and pointer to next Node as parameter input)
  * @post Contents of Node are copied from parameter node, including next pointer.
  */
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr):
 item(anItem), next(nextNodePtr){

} // end constructor

/** Set item in node to input
  * @post item in node has been set to input
  */
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem){
	item = anItem;
} // end setItem

/** Set the next pointer
  * @post next pointer now set to parameter input pointer
  */
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr){
	next = nextNodePtr;
} // end setNext

/** Retrieve the data in the node
  * @return the data item was storing
  */
template<class ItemType>
ItemType Node<ItemType>::getItem() const{
	return item;
} // end getItem

/** Find the node the next pointer is pointing at
  * @return A pointer pointing to the next node
  */
template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const{
	return next;
} // end getNext