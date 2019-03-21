/**
  * @file LinkedList.h
  *
  * @brief Header file for LinkedList creation
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

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedList : public ListInterface<ItemType>{
private:
	Node<ItemType>* headPtr; // Pointer to first node in the chain
	// (contains the first entry in the list)
	int itemCount; // Current count of list items
	
	/** Locates a specified node in a linked list.
	  *	@pre position is the number of the desired node;
	  *	position >= 1 and position <= itemCount.
	  *	@post The node is found and a pointer to it is returned.
	  *	@param position The number of the node to locate.
	  *	@return A pointer to the node at the given position.
	  */
	Node<ItemType>* getNodeAt(int position) const;

public:
	/** Default constructor for the LinkedList class
	  * @pre LinkedList object does not exist
	  * @post The LinkedList object has been created
	  * with default values
	  */
	LinkedList();

	/** Copy constructor for the LinkedList class
	  * @pre Two LinkedList object exists
	  * @post The contents of the parameter LinkedList
	  * is copied into the parent class.
	  * @param aList The LinkedList to be copied
	  */
	LinkedList(const LinkedList<ItemType>& aList);

	/** Deconstructor for the LinkedList class
	  * @pre LinkedList object is in memory
	  * @post LinkedList object is removed from memory
	  */
	virtual ~LinkedList();

	/** Checks if the LinkedList is empty
	  * @pre Unknown if state of LinkedList is empty
	  * @post State of LinkedList is known
	  * @return A bool determining if LinkedList is empty
	  */
	bool isEmpty() const;

	/** Find the number of objects in the LinkedList
	  * @pre Number of objects in LinkedList is unknown
	  * @post Number of objects in LinkedList is known
	  * @return An int representing number of objects in the LinkedList
	  */
	int getLength() const;

	/** Insert an entry to the LinkedList at the specified position
	  * @pre LinkedList is in its present state
	  * @post LinkedList has an entry inserted at the position
	  * provided by the parameter
	  * @param newPosition Where in the list the entry should be inserted
	  * @param newEntry The item to be inserted into the list
	  * @return A bool specifying what if the insertion was successful
	  */
	bool insert(int newPosition, const ItemType& newEntry);

	/** Remove an entry in the LinkedList at the specified position
	  * @pre LinkedList is in its present state
	  * @post Entry at the specified position has been removed from the list
	  * @param position Where in the list the entry should be removed
	  * @return A bool specifying if the removal was successful
	  */
	bool remove(int position);

	/** Remove first object from the list until the list is empty
	  * @pre LinkedList is in its present state
	  * @post all objects in the list are removed
	  */
	void clear();

	/** Find the entry at the point specified in the list
	  * @pre The entry at a certain point in the list is unknown
	  * @post The entry at a certain point in the list is known
	  * @param position Where in the list the entry should be returned
	  * @return The entry at the position in the LinkedList
	  * @throw PrecondViolatedExcep if position < 1 or
	  * position > getLength().
	  */
	ItemType getEntry(int position) const throw(PrecondViolatedExcep);

	/** Replaces the entry at a given point
	  * @pre  1 <= position <= getLength().
      * @post  The entry at the given position is newEntry.
      * @param position  The list position of the entry to replace.
      * @param newEntry  The replacement entry.
	  * @throw PrecondViolatedExcep if position < 1 or
		position > getLength().
	  */
	void replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcep);
};

#include "LinkedList.cpp"
