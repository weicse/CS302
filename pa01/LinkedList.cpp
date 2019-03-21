/**
  * @file LinkedList.cpp
  *
  * @brief Implementation file for LinkedList creation
  *
  * @details Creates function prototype for the linked list used in the linked list
  *
  * @version 1.00
  *		Wei Tong (15 September 2016)
  *		Initial development of the linked list class
  *
  * @note
  *		Adapted from Frank M. Carrano and Timothy M. Henry
  * 	Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "LinkedList.h"
#include <cassert>
#include <cstddef>


/** Default constructor for the LinkedList class
  * @pre LinkedList object does not exist
  * @post The LinkedList object has been created
  * with default values
  */
template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0){

}

/** Copy constructor for the LinkedList class
  * @pre Two LinkedList object exists
  * @post The contents of the parameter LinkedList
  * is copied into the parent class.
  * @param aList The LinkedList to be copied
  */
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList){
	
}

/** Deconstructor for the LinkedList class
  * @pre LinkedList object is in memory
  * @post LinkedList object is removed from memory
  */
template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
    delete headPtr;
    headPtr = nullptr;
}

/** Checks if the LinkedList is empty
  * @pre Unknown if state of LinkedList is empty
  * @post State of LinkedList is known
  * @return A bool determining if LinkedList is empty
  */
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}

/** Find the number of objects in the LinkedList
  * @pre Number of objects in LinkedList is unknown
  * @post Number of objects in LinkedList is known
  * @return An int representing number of objects in the LinkedList
  */
template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
}

/** Insert an entry to the LinkedList at the specified position
  * @pre LinkedList is in its present state
  * @post LinkedList has an entry inserted at the position
  * provided by the parameter
  * @param newPosition Where in the list the entry should be inserted
  * @param newEntry The item to be inserted into the list
  * @return A bool specifying what if the insertion was successful
  */
template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry 
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);  
      
      // Attach new node to chain
      if (newPosition == 1)
      {
         // Insert new node at beginning of chain
         newNodePtr->setNext(headPtr); 
         headPtr = newNodePtr;
      }
      else
      {
         // Find node that will be before new node
         Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
         
         // Insert new node after node to which prevPtr points
         newNodePtr->setNext(prevPtr->getNext()); 
         prevPtr->setNext(newNodePtr);
      }

      itemCount++;  // Increase count of entries
   }

   return ableToInsert;
}

/** Remove an entry in the LinkedList at the specified position
  * @pre LinkedList is in its present state
  * @post Entry at the specified position has been removed from the list
  * @param position Where in the list the entry should be removed
  * @return A bool specifying if the removal was successful
  */
template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      Node<ItemType>* curPtr = nullptr;
      if (position == 1)
      {
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
      }
      else
      {
         // Find node that is before the one to delete
         Node<ItemType>* prevPtr = getNodeAt(position - 1);
         
         // Point to node to delete
         curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  
      
      // Return node to system
      curPtr->setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      
      itemCount--;  // Decrease count of entries
   }
   
   return ableToRemove;
}

/** Remove first object from the list until the list is empty
  * @pre LinkedList is in its present state
  * @post all objects in the list are removed
  */
template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}

/** Find the entry at the point specified in the list
  * @pre The entry at a certain point in the list is unknown
  * @post The entry at a certain point in the list is known
  * @param position Where in the list the entry should be returned
  * @return The entry at the position in the LinkedList
  * @throw PrecondViolatedExcep if position < 1 or
  * position > getLength().
  */
template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      std::string message = "getEntry() called with an empty list or "; 
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }
}

/** Replaces the entry at a given point
  * @pre  1 <= position <= getLength().
  * @post  The entry at the given position is newEntry.
  * @param position  The list position of the entry to replace.
  * @param newEntry  The replacement entry.
  * @throw PrecondViolatedExcep if position < 1 or
	position > getLength().
  */
template<class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcep) 
{
	// Enforce precondition
	bool ableToSet = (position >= 1) && (position <= itemCount);
	if (ableToSet)
	{
		insert(position, newEntry);
	}
	else
	{
		std::string message = "replace() called with "; 
		message  = message + "invalid position.";
		throw(PrecondViolatedExcep(message)); 
	}
}

/** Locates a specified node in a linked list.
  *	@pre position is the number of the desired node;
  *	position >= 1 and position <= itemCount.
  *	@post The node is found and a pointer to it is returned.
  * @param position The number of the node to locate.
  * @return A pointer to the node at the given position.
  */
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );
   
   // Count from the beginning of the chain
   Node<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();
      
   return curPtr;
}

#endif