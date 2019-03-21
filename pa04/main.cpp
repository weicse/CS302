/**
  *	@file main.cpp
  *
  *	@brief Put the three algorithms to use
  *	@details Main file for project. Will call upon
  *	functions to read in data, and sort them with
  *	insertion, merge, and bucket with merge sort.
  *
  *	@version 1.00
  *			Wei Tong (1 November 2016)
  *			Turned in version and initial development
  *	@note
  *			Adapted from Frank M. Carrano and Timothy M. Henry
  *			Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */

#include "Algorithm.h"


/** Runs the three sorts 10 times each on sorted and unsorted data
  *
  * @pre Random data has already been generated, but not sorted
  * @post Insertion sort, merge sort, and bucket sort have been run
  * 10 times on the unsorted and sorted data, and the statistics and
  * their averages have been outputted to their specific file
  *
  * @param thisData The class containing the randomly sorted data, as
  * well as the functions to sort said data
  * @param iSort fstream for the output of insertion sort's statistics
  * @param mSort fstream for the output of merge sort's statistics
  * @param bSort fstream for the output of bucket sort's statistics
  * @param size the amount of data to take into consideration
  *
  */
void run_all(mySort& thisData, fstream& iSort, fstream& mSort, fstream & bSort, int size){
	int i;
	unsigned long long swaps, comps; // The number of swaps and comparisons
	unsigned long long iSwapAVG = 0, iCompAVG = 0, iCpuAVG = 0; // For insert sort
	unsigned long long mSwapAVG = 0, mCompAVG = 0, mCpuAVG = 0; // For merge sort
	unsigned long long bSwapAVG = 0, bCompAVG = 0, bCpuAVG = 0; // For bucket sort
	clock_t timer;

	iSort << "Insertion Sort with " << size << " random numbers\nTrial #\tSwaps\tCompares\tClock ticks\n";
	mSort << "Merge Sort with " << size << " random numbers\nTrial #\tSwaps\tCompares\tClock ticks\n";
	bSort << "Bucket Sort with " << size << " random numbers\nTrial #\tSwaps\tCompares\tClock ticks\n";
	for(i = 0; i < 10; i++){ // Run 10 times for data to use for averages
		// Insert Sort
		thisData.readIn(); // Read in the randomly sorted data from file
		thisData.prepData(); // Set the number of swaps and compares to zero
		timer = clock(); // Start the timer
		thisData.insertSort(); // Do insertion sort
		timer = clock() - timer; // Find the time since timer started
		thisData.getSortInfo(swaps, comps); // Retrieve the number of swaps and compares
		iSort << i << "\t" << swaps << "\t" << comps << "\t" << timer << "\n"; // Output to file
		iSwapAVG += swaps; // Add the amount of swaps to the average
		iCompAVG += comps; // Add the amount of compares to the average
		iCpuAVG += timer; // Add the amount of time to the average

		// Merge Sort
		thisData.readIn();
		thisData.prepData();
		timer = clock();
		thisData.mergeSort(0, thisData.getSize());
		timer = clock() - timer;
		thisData.getSortInfo(swaps, comps);
		mSort << i << "\t" << swaps << "\t" << comps << "\t" << timer << "\n";
		mSwapAVG += swaps;
		mCompAVG += comps;
		mCpuAVG += timer;

		// Bucket Sort
		thisData.readIn();
		thisData.prepData();
		timer = clock();
		thisData.bucketSort();
		timer = clock() - timer;
		thisData.getSortInfo(swaps, comps);
		bSort << i << "\t" << swaps << "\t" << comps << "\t" << timer << "\n";
		bSwapAVG += swaps;
		bCompAVG += comps;
		bCpuAVG += timer;
	}
	iSort << "Avg." << "\t" << iSwapAVG / 10 << "\t" << iCompAVG / 10 << "\t" << iCpuAVG / 10 << "\n";
	mSort << "Avg." << "\t" << mSwapAVG / 10 << "\t" << mCompAVG / 10 << "\t" << mCpuAVG / 10 << "\n";
	bSort << "Avg." << "\t" << bSwapAVG / 10 << "\t" << bCompAVG / 10 << "\t" << bCpuAVG / 10 << "\n";

	thisData.readOut(); // Write sorted data to file
	iSwapAVG = 0, iCompAVG = 0, iCpuAVG = 0; // Reset the statistics
	mSwapAVG = 0, mCompAVG = 0, mCpuAVG = 0;
	bSwapAVG = 0, bCompAVG = 0, bCpuAVG = 0;
	iSort << "\nInsertion Sort with " << size << " sorted numbers\nTrial #\tSwaps\tCompares\tClock ticks\n";
	mSort << "\nMerge Sort with " << size << " sorted numbers\nTrial #\tSwaps\tCompares\tClock ticks\n";
	bSort << "\nBucket Sort with " << size << " sorted numbers\nTrial #\tSwaps\tCompares\tClock ticks\n";
	for(i = 0; i < 10; i++){
		// Insert Sort
		thisData.readIn();
		thisData.prepData();
		timer = clock();
		thisData.insertSort();
		timer = clock() - timer;
		thisData.getSortInfo(swaps, comps);
		iSort << i << "\t" << swaps << "\t" << comps << "\t" << timer << "\n";
		iSwapAVG += swaps;
		iCompAVG += comps;
		iCpuAVG += timer;

		// Merge Sort
		thisData.readIn();
		thisData.prepData();
		timer = clock();
		thisData.mergeSort(0, thisData.getSize());
		timer = clock() - timer;
		thisData.getSortInfo(swaps, comps);
		mSort << i << "\t" << swaps << "\t" << comps << "\t" << timer << "\n";
		mSwapAVG += swaps;
		mCompAVG += comps;
		mCpuAVG += timer;

		// Bucket Sort
		thisData.readIn();
		thisData.prepData();
		timer = clock();
		thisData.bucketSort();
		timer = clock() - timer;
		thisData.getSortInfo(swaps, comps);
		bSort << i << "\t" << swaps << "\t" << comps << "\t" << timer << "\n";
		bSwapAVG += swaps;
		bCompAVG += comps;
		bCpuAVG += timer;
	}

	iSort << "Avg." << "\t" << iSwapAVG / 10 << "\t" << iCompAVG / 10 << "\t" << iCpuAVG / 10 << "\n\n";
	mSort << "Avg." << "\t" << mSwapAVG / 10 << "\t" << mCompAVG / 10 << "\t" << mCpuAVG / 10 << "\n\n";
	bSort << "Avg." << "\t" << bSwapAVG / 10 << "\t" << bCompAVG / 10 << "\t" << bCpuAVG / 10 << "\n\n";
}

int main(){
	fstream iSort, mSort, bSort;
	iSort.open("iSort", fstream::out | fstream::trunc); // for insert sort data
		// The extra parameters help clear file before writing to it
	mSort.open("mSort", fstream::out | fstream::trunc); // For merge sort data
	bSort.open("bSort", fstream::out | fstream::trunc); // For bucket sort data

	mySort first(1000); // Create class for 1000 items
	first.RNG(); // Generate the random numbers
	run_all(first, iSort, mSort, bSort, 1000); // Run all three sorts on 1000 items
	
	mySort second(10000);
	second.RNG();
	run_all(second, iSort, mSort, bSort, 10000);
/*
	mySort third(100000);
	third.RNG();
	run_all(third, iSort, mSort, bSort, 100000);

	mySort fourth(1000000);
	fourth.RNG();
	run_all(fourth, iSort, mSort, bSort, 1000000);
*/
	iSort.close(); // Finish writing to file
	mSort.close();
	bSort.close();

	return 0;
}