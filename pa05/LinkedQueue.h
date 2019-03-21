#include "Node.h"

class LinkedQueue{
	Node* backPtr;
	Node* frontPtr;

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& aQueue);
	~LinkedQueue();

	bool isEmpty() const;
	bool enqueue(const int& newEntry);
	bool dequeue();

	int peekFront();
};