class Node{
	int item;
	Node* next;

public:
	Node();
	Node(const int& anItem);
	Node(const int& anItem, Node* nextNodePtr);
	void setItem(const int& anItem);
	void setNext(Node* nextNodePtr);
	int getItem() const;
	Node* getNext() const;
};