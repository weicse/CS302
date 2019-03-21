/**
  * @file main.cpp
  *
  * @brief Test driver of binary search tree implementation
  * @details Main file for project. Will generate an amount
  * of random data specified by SIZE_FIRST, between 1 and 200
  * and put them into the first binary search tree. A second
  * set of random data, the amount specified by SIZE_SECOND
  * will be created. This set however, will take a random
  * amount of numbers between 1 and its max size, and fill
  * that amount of number with random numbers from the first
  * BST. The remaining numbers will be randomly generated. For
  * both BSTs, there will be no repeat numbers.
  *
  * @version 1.00
  * 		Wei Tong (11 November 2016)
  * 		Turned in version and initial development
  *
  * @note
  * 		Adapted from Frank M. Carrano and Timothy M. Henry
  *			Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */
#include "BinaryNode.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#define SIZE_FIRST 100
#define SIZE_SECOND 10
ofstream fout; // Global to allow all functions to access without passing
BinarySearchTree first, second; // First and second binary tree

/** Removes data in the BST as it traverses
  *
  * @post The first BST will have data removed
  * from it as the BST that calls upon this traverse
  * is traversed. All numbers that are in both the
  * BSTs are removed from the first BST
  *
  * @param data The number at the node currently being visited
  * and will be removed from the first BST if it exists
  */
void removeTraverse(int& data){
	first.remove(data);
}

/** Removes data in the BST as it traverses
  *
  * @post The data of the node currently being visited will be
  * output to the file
  *
  * @param data The number at the node currently being visited
  * and will be outputted from the BST
  */
void traverseOutput(int& data){
	fout << data << endl;
}

int main(){

	srand(time(NULL)); // Seed the RNG with time

	fout.open("myOutput");
	int i, j, firstData[SIZE_FIRST], secondData[SIZE_SECOND];

//------------NUMBER ONE OF ASSIGNMENT-----------------------

	for(i = 0; i < SIZE_FIRST; i++){ // Create the specified amount of random numbers
		firstData[i] = rand() % 200 + 1; // Specify size between 1 and 200
		for(j = 0; j < i; j++){ // Loop to check if copies exist already
			if(firstData[i] == firstData[j]){ // Ensure there are no copies
				j = -1; // Start over to recheck entire array for copies
				firstData[i] = rand() % 200 + 1; // Make new random number
			}
		}
	}

	fout << "Randomly generated data for first BST:" << endl;
	for(i = 0; i < SIZE_FIRST; i++){
		fout << firstData[i] << endl; // Output randomly generated number (not sorted) to file
		first.add(firstData[i]); // Add the numbers to the first BST
	}

	fout << "Height of first BST: " << first.getHeight() << endl;
	fout << "First BST inorder:" << endl;
	first.inorderTraverse(traverseOutput);

//------------NUMBER TWO OF ASSIGNMENT-----------------------

	for(i = 0; i < rand() % SIZE_SECOND + 1; i++){ // Take random amount of numbers from first BST
		secondData[i] = firstData[rand() % SIZE_FIRST]; // Random number from first BST
		for(j = 0; j < i; j++){
			if(secondData[i] == secondData[j]){ // Ensure there are no copies
				j = -1;
				secondData[i] = firstData[rand() % SIZE_FIRST];
			}
		}
	}

	for( ; i < SIZE_SECOND; i++){ // Make random numbers
		secondData[i] = rand() % 200 + 1;
		for(j = 0; j < SIZE_FIRST; j++){ // Ensure not already used before
			if(secondData[i] == firstData[j]){
				j = -1;
				secondData[i] = rand() % 200 + 1;
			}
		}
	}

	fout << "Randomly generated data for second BST" << endl;
	for(i = 0; i < SIZE_SECOND; i++){
		fout << secondData[i] << endl;
		second.add(secondData[i]); // Output unosrted randomly generated numbers
	}

	fout << "Second BST preorder:" << endl;
	second.preorderTraverse(traverseOutput);
	fout << "Second BST inorder:" << endl;
	second.inorderTraverse(traverseOutput);
	fout << "Second BST post:" << endl;
	second.postorderTraverse(traverseOutput);

//------------NUMBER THREE OF ASSIGNMENT-----------------------

	second.inorderTraverse(removeTraverse);
	fout << "Modified BST #1 height:" << first.getHeight() << endl;
	fout << "Modified BST #1 number of nodes:" << first.getNumberOfNodes() << endl;
	fout << "Modified BST #1 inorder output:" << endl;
	first.inorderTraverse(traverseOutput);

//------------NUMBER FOUR OF ASSIGNMENT-----------------------

	fout << "Is first BST empty? ";
	if(first.isEmpty()){ // This looks nicer to me than outputting 0 or 1
		fout << "Yes" << endl;
	}
	else{
		fout << "No" << endl;
	}

	fout << "Is second BST empty? ";
	if(second.isEmpty()){
		fout << "Yes" << endl;
	}
	else{
		fout << "No" << endl;
	}

	first.clear();
	second.clear();
	fout << "Both BST have been cleared." << endl;

	fout << "Is first BST empty? ";
	if(first.isEmpty()){
		fout << "Yes" << endl;
	}
	else{
		fout << "No" << endl;
	}

	fout << "Is second BST empty? ";
	if(second.isEmpty()){
		fout << "Yes" << endl;
	}
	else{
		fout << "No" << endl;
	}

	fout.close(); // Important to close file

	return 0;
}