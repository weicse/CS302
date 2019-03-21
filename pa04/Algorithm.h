#include <iostream>
#include <fstream>
using namespace std;

class mySort{
	int* myData, size;
	unsigned long long numComps, numSwaps;
public:
	mySort(int);
	~mySort();
	int getSize();
	void display();
	void readIn();
	void readOut();
	void RNG();
	void insertSort();
	void merge(int, int, int);
	void mergeSort(int, int);
	void bucketSort();
	void prepData();
	void getSortInfo(unsigned long long&, unsigned long long&);
};