#include "LinkedQueue.h"
#include <cassert>

/*
Default constructor that sets the back and front pointers to null
*/
LinkedQueue::LinkedQueue(){
	backPtr = 0;
	frontPtr = 0;
}

/*
Copy constructor
@param aQueue Copies a queue
*/
LinkedQueue::LinkedQueue(const LinkedQueue& aQueue){
	Node* origChainPtr = aQueue.frontPtr;
	if(origChainPtr == 0){
		frontPtr = 0;
		backPtr = 0;
	}
	else{
		frontPtr = new Node();
		frontPtr->setItem(origChainPtr->getItem());
		origChainPtr = origChainPtr->getNext();

		Node* newChainPtr = frontPtr;
		while(origChainPtr != 0){
			int nextItem = origChainPtr->getItem();
			Node* newNodePtr = new Node(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(0);
		backPtr = newChainPtr;
	}
}

/*
Deconstructor
@post Everything inside the queue is deleted
*/
LinkedQueue::~LinkedQueue(){
	while(!isEmpty()){
		dequeue();
	}
	assert((backPtr == 0) && (frontPtr == 0));
}

/*
Check if the queue is empty
*/
bool LinkedQueue::isEmpty() const{
	return backPtr == 0;
}

/*
Pushes a new entry into the queue
@param newEntry The data to be pushed to the queue
@return if successful or not
*/
bool LinkedQueue::enqueue(const int& newEntry){
	Node* newNodePtr = new Node(newEntry);
	if(isEmpty()){
		frontPtr = newNodePtr;
	}
	else{
		backPtr->setNext(newNodePtr);
	}
	backPtr = newNodePtr;
	return true;
}

/*
Removes an object from the front of the queue
@return if successful or not
*/
bool LinkedQueue::dequeue(){
	bool result = false;
	if(!isEmpty()){
		Node* nodeToDeletePtr = frontPtr;
		if(frontPtr == backPtr){
			frontPtr = 0;
			backPtr = 0;
		}
		else{
			frontPtr = frontPtr->getNext();
		}
		nodeToDeletePtr->setNext(0);
		delete nodeToDeletePtr;
		result = true;
	}
	return result;
}

/*
Gets the value at the front of the queue
@return item stored at front of queue
*/
int LinkedQueue::peekFront(){
	return frontPtr->getItem();
}