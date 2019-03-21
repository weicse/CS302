//  Created by Shehryar Khattak for CS302 Spring 2016 class.
/**
  * @file main.cpp
  *
  * @brief Binary search for kth smallest value in array
  *
  * @details A list of numbers is read in from a file and stored
  * into an array. A pivot is then chosen, and the array is sorted
  * partially (only the portion smaller than the pivot). This is
  * repeated recursively until the value is found.
  *
  * @version 1.01
  * 	Wei Tong (3 October 2016)
  * 	Final completed version
  *
  * @version 1.00
  * 	Shehryar Khattak
  * 	Initial development of main file
  *
  * @note
  * 	Adapted from Frank M. Carrano and Timothy M. Henry
  * 	Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */
#include <iostream>
#include <fstream>
using namespace std;

/** Partial sort and binary search of the array
  *
  * @param k The kth smallest value of the data
  * @param anArray[] The array containing the data
  * @param first What is considered the first index in the array
  * @param last What is considered the last index in the array
  * @param logging fstream to output the logging to log.txt
  *
  * @post The data in indexes smaller than the pivot are sorted
  * and the next step is decided based on if the value to be found
  * is smaller, larger, or the same as the pivot.
  *
  * @return The integer from a recursion of the same function, if
  * the k value is larger or smaller than the pivot
  *
  * @return The pivot index, if the k value is the same as the pivot
  */
int kSmall(int k, int anArray[], int first, int last, fstream& logging){

	int pivotIndex = (first + last) / 2;

	/*
	for(int i = first; i < last; i++){
		cout << anArray[i] << " ";
	}
	cout << endl;

	cout << "First: " << first << ", Last: " << last << ", Pivot: " << pivotIndex << ", k: " << k << endl;
	*/

	int myFirst, myLast = last, tmp;
	while(myLast >= pivotIndex){
		myFirst = first;
		while(myFirst <= pivotIndex){
			if(anArray[myFirst] > anArray[myLast]){
				tmp = anArray[myFirst];
				anArray[myFirst] = anArray[myLast];
				anArray[myLast] = tmp;
			}
			myFirst++;
		}
		myLast--;
	}	//The array is shuffled to have all the values smaller than the pivot placed on the left of the pivot

	logging << "Pivot is at: " << pivotIndex << endl;
	for(int i = first; i <= last; i++){
		logging << anArray[i];
		if(i != last){
			logging << " ";
		}
	}
	logging << endl;
	//Logging is outputted to file

	if(k < pivotIndex - first + 1){
		return kSmall(k, anArray, first, pivotIndex - 1, logging);
	}	//If the k value is less than the pivot

	else if(k == pivotIndex - first + 1){
		return anArray[pivotIndex];
	}	//Base case, returned if k value is the same as the index

	else{
		return kSmall(k - (pivotIndex - first + 1), anArray, pivotIndex + 1, last, logging);
	}	// If the k value is greater than the pivot
}


int main(){

	//Declerations (insert as needed)
	int kSmall_pos;			//For User Input
	int kSmall_val = 0;		//Populate using your algorithm implementation
	int arr[512];			//Array to input data to
	int big = 0;			//Keeps track of how big the array actually is
	char fileName[25];		//Name of file to be read from


	//File Read code (insert) - This code should be able to parse the data in a text file similar to the provided one and store values in an array for processing.
	
	cout << "Please enter the name of the file: ";
	cin >> fileName;	//User decides which file to use
	
	fstream data;
	data.open("data");	//fstream to read in data from said file

	while(!data.eof()){
		if(data >> arr[big]);
		
		else{
			cout << "Error reading file, quitting." << endl;
			return 0;
		}	// If file does not exist, or an error occurred.
		
		big++;
	}

	data.close();


	//User Input DO NOT MODIFY
	cout << "Please enter required kth smallest value: ";
	cin >> kSmall_pos;


	//kmsall algorithm implementation or function call (insert) - implement using recursion as indicated
	if(kSmall_pos == 0 || kSmall_pos > big){
		cout << "Error, kth value is out of bounds" << endl;
		return 0;
	}	//Prevent searching indexes that don't exist

	fstream outputLog;
	outputLog.open("log.txt", fstream::out | fstream::trunc);
	//Output log is done within the function
	kSmall_val = kSmall(kSmall_pos, arr, 0, big - 1, outputLog);
	outputLog.close();

	//Output DO NOT MODIFY
	cout << "kth smallest value = " << kSmall_val << endl;
}