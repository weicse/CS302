class LinkedQueue{
	int back, front;
	int* data;
public:
	LinkedQueue();
	~LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const int& newEntry);
	bool dequeue();

	int peekFront();
};