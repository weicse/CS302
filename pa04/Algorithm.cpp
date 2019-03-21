#include <cstdlib>
#include <ctime>
#include "Algorithm.h"

/**	Constructor for the class that stores and sorts data
  *
  *	@post An ADT is created, but empty
  *
  *	@param howBig The amount of data to be considered
  */
mySort::mySort(int howBig){
	size = howBig; // Set the array to fit the amount of data
	myData = new int[size];
	numComps = 0; // Set the number of compares to zero
	numSwaps = 0; // Set the number of swaps to zero
}

/**	Deconstructor for the mySort class
  *
  *	@pre ADT is going out of scope
  *	@post dynamically allocated array is deleted
  */
mySort::~mySort(){
	delete[] myData;
}

/**	Find the amount of data the ADT stores
  *
  *	@return the integer size
  */
int mySort::getSize(){
	return size;
}

void mySort::display(){
	for(int i = 0; i < size; i++){
		cout << myData[i] << '\n';
	}
}

/**	Read in a list of numbers from the file "data"
  *
  *	@post Data is read into the myData array
  */
void mySort::readIn(){
	fstream fin;
	fin.open("data");
	for(int i = 0; i < size; i++){
		fin >> myData[i];
	}
	fin.close();
}

/**	Outputs the data in the myData array to file "data"
  *
  *	@post file "data" contains all data from the myData array
  */
void mySort::readOut(){
	fstream fout;
	fout.open("data", fstream::out | fstream::trunc);
	for(int i = 0; i < size; i++){
		fout << myData[i] << '\n';
	}
	fout.close();
}

/**	Generates a list of random numbers
  *
  *	@post The myData array and "data" file contain a list
  * of the same randomly generated numbers between 0 and 1,000,000
  */
void mySort::RNG(){
	int tmp;
	fstream fout;
	fout.open("data", fstream::out | fstream::trunc);
	for(int i = 0; i < size; i++){
		tmp = rand() % 1000000; // Will generate numbers between 0 and 1 million
		fout << tmp << '\n';
			// Newline instead of endl, because endl is too resource intensive
		myData[i] = tmp;
	}
	fout.close();
}

/**	Sorts the data using insertion sort algorithm
  *
  *	@pre Numbers in the myData array are unsorted
  *	@post Numbers in the myData array are sorted
  */
void mySort::insertSort(){
	int nextItem, loc, unsorted;
		// nextItem = next item in the unsorted region
		// loc = index of insertion in sorted region
	for(unsorted = 1; unsorted < size; unsorted++){
		nextItem = myData[unsorted];
		loc = unsorted;
		while((loc > 0) && (myData[loc-1] > nextItem)){
			numComps++; // Increment the number of compares
			myData[loc] = myData[loc - 1];
				// Shifts data to the right
			numSwaps++, loc--; // Increment number of swaps
		}
		numComps++;
		myData[loc] = nextItem; // Insert nextItem into sorted region
	}
}

/**	Do the actual sorting in merge sort algorithm
  *
  *	@pre first <= mid <= last. The arrays are sorted in increasing order
  *	@post theArray[first, last] is sorted
  *
  *	@param first index of beginning of segment in the array
  *	@param mid index of the end of the first segment in the array
  *	@param last index of last element in second array
  *
  *	@note This function merges two subarrays into a temporary array
  */
void mySort::merge(int first, int mid, int last){
	int tempArray[size];
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	// Copy data in smaller array into temporary Array
	int index = first1; // Next available location in tempArray
	while((first1 <= last1) && (first2 <= last2)){
		// tempArray[first -> index - 1] should be in order
		if(myData[first1] <= myData[first2]){
			tempArray[index] = myData[first1];
			first1++;
		}
		else{
			tempArray[index] = myData[first2];
			first2++;
		}
		numComps++, numSwaps++, index++; // Compared only once
	}

	// Finish first array if needed
	while(first1 <= last1){
		tempArray[index] = myData[first1];
		numSwaps++, first1++, index++;
	}

	// Finish second array if needed
	while(first2 <= last2){
		tempArray[index] = myData[first2];
		numSwaps++, first2++, index++;
	}

	// Copy sorted data back to original array
	for(index = first; index <= last; index++){
		myData[index] = tempArray[index];
		numSwaps++;
	}
}

/**	Sorts items in ascending order
  *
  *	@pre myData is an array of unsorted numbers
  *	@post myData is sorted in ascending order
  *
  *	@param first first element to consider sorting
  *	@param last last element to consider sorting
  */
void mySort::mergeSort(int first, int last){
	if(first < last){
		int mid = first + (last - first) / 2;
		mergeSort(first, mid);
			// Sort left half of the array
		mergeSort(mid + 1, last);
			// Sort right half of the array
		merge(first, mid, last);
			// Merge the two halves
	}
}

/**	Sorts items in ascending order
  *
  *	@pre myData is an array of unsorted numbers
  *	@post myData is sorted in ascending order
  *
  *	@note This function will create 10 buckets,
  * and arrange the array so the numbers that are
  * x/10 of the max size (x being the bucket #, starting with 1)
  * are placed together, and that segment of the array is sorted
  * using merge sort
  *
  *	@note This only really works for data sets that are
  * sizes of multiples of ten (anthing else might cut off a number)
  */
void mySort::bucketSort(){
	int index = 0, prev_index = 0, bucket = size / 10, b_max = 100000;
		// Create 10 buckets
	int j, i;
	for(j = 0; j < 10; j++){
		// Run everything below for each bucket
		while(myData[index] < b_max && index < size){
			numComps++, index++;
		}
		for(i = index; i < size; i++){
			// Go through array and sort into buckets
			if(myData[i] < b_max && i != index){
				swap(myData[i], myData[index]);
				numSwaps++, index++; // Swapped once
			}
			numComps++; // Compared once
		}
		mergeSort(prev_index, index);
			// merge sort each bucket before sorting next part
		prev_index = index;
		b_max += 100000; // Increase size of b_max
	}
}

/**	Resets the counters for compares and swaps
  *
  *	@post the counters for compares and swaps is reset
  */
void mySort::prepData(){
	numComps = 0, numSwaps = 0; // Reset counters
}

/**	Gets the number of compares and swaps
  *
  *	@param swaps unsigned long long to hold the number of swaps
  * @param comps unsigned long long to hold the number of compares
  */
void mySort::getSortInfo(unsigned long long& swaps, unsigned long long& comps){
	swaps = numSwaps;
	comps = numComps;
}