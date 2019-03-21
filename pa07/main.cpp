/**
  * @file BinarySearchTree.h
  *
  * @brief Header file for binary search tree
  * @details Some of the functions that are irrelevant
  * to this assignment have been removed (and thus not implemented)
  *
  * @version 1.00
  * 		Wei Tong (13 December 2016)
  * 		Turned in version and initial development
  */

#include "BinaryNode.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>
using namespace std;

fstream fin, fout; // Global for easier access accross function
BinarySearchTree first;
int total_sum = 0;

/** Traverses throughout the tree, adding numbers as it goes
  *
  * @param data The number at the node in the tree
  */
void traverseOutput(int& data){
	total_sum += data;
}

int main(){

	fin.open("data"); // Read data numbers
	fout.open("myOutput"); // Output file

	int tmp;
	for(int i = 0; i < 10; i++){
		fin >> tmp;
		first.add(tmp);
	}
	fout << "Height of tree: " << first.getHeight() << endl;
	first.inorderTraverse(traverseOutput);
	fout << "Sum of all values: " << total_sum << endl;
	fout << "Is the binary tree empty? ";
	if(first.isEmpty()){
		fout << "Yes" << endl;
	}
	else{
		fout << "No" << endl;
	}
	first.clear();
	fout << "Binary tree cleared.\nIs the binary tree empty? ";
	if(first.isEmpty()){
		fout << "Yes" << endl;
	}
	else{
		fout << "No" << endl;
	}

	/* NOTE
	 *
	 * This program seems to work with 10 integers, and more.
	 * However, there are very specific cases that it does not work,
	 * which I couldn't figure out how to work out.
	 */

	fin.close();
	fout.close();

	return 0;
}