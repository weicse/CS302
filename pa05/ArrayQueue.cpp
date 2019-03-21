#include "ArrayQueue.h"

/*
Default constructor for array based implementation
@note When front and back point to the same place, the queue is empty
*/
LinkedQueue::LinkedQueue(){
	// Could ask user for data size if needed
	data = new int[100000];
	front = 0, back = 0;
}

/*
Deconstructor for array queue
@post the dynamically allocated array is deleted
*/
LinkedQueue::~LinkedQueue(){
	delete[] data;
	data = 0;
}

/*
Check if the queue is empty or not
@return if the queue is empty or not
*/
bool LinkedQueue::isEmpty() const{
	return(front == back);
}

/*
Add an item to the queue
@param newEntry new data to be stored in the queue
@return if successfully added item
*/
bool LinkedQueue::enqueue(const int& newEntry){
	if(back == (front + 1) % (100000)){
		return false;
	}
	else{
		data[front] = newEntry;
		front = (front + 1) % (100000);
	}
}

/*
Remove item from top of queue
@return if successful or not
*/
bool LinkedQueue::dequeue(){
	if(isEmpty()){
		return false;
	}
	else{
		back = (back + 1) % (100000);
		return true;
	}
}

/*
Find the value of the front object of the queue
@return data stored at front of queue
*/
int LinkedQueue::peekFront(){
	return data[back];
}