/*
@file main.cpp
@brief Use node and array based simulation for bank tellers
@details Main file for project. Will call upon
functions to simulate one queue one teller, one queue three
tellers, or three queue three tellers. File must be slightly
modified depending on if the node or array based
implementation is to be used.

@version 1.00
	Wei Tong (15 November 2016)
	Turned in version and initial development
@note
	Adapted from Frank M. Carrano and Timothy M. Henry
	Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
*/

//#include "LinkedQueue.h"
#include "ArrayQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

/*	To compile for linked queue, uncomment line 1 and comment out line 2
	Then type "make link"

	To compile for array queue, comment out line 2 and uncomment line 1
	Then type "make array"
*/


/*
@post Data is read in and the simulation has been run with one line and one teller
@param simt use to store how long the simulation takes
@param awt use to store how long the average waiting time is
@param mwt use to store the maximum waiting time
@param twt use to store the total wait time
@param mll use to store the max line length
@param idt use to store the idle teller time
*/
void OneOne(float& simt, float& awt, float& mwt, float& twt, float& mll, float& idt){

	fstream fin;
	fin.open("data");

	LinkedQueue cTime, cDuration, cLine, cLineDuration;
	bool Teller = true;
	float timer = 0, departTime = 0, numCustomers = 0, tmp = 0;
	float totalWaitTime = 0, maxWaitTime = 0, lineLength = 0, maxLineLength = 0, idleTime = 0;

	int aTime, aDur;
	while(!fin.eof()){
		fin >> aTime >> aDur;
		numCustomers++;
		cTime.enqueue(aTime);
		cDuration.enqueue(aDur);
	}

	while(!cTime.isEmpty() || !Teller){
		if(!cTime.isEmpty() && (Teller || cTime.peekFront() < departTime)){
			if(cLineDuration.isEmpty() && Teller){
				idleTime += cTime.peekFront() - departTime;
			}
			if(Teller){
				Teller = false;
				timer = cTime.peekFront();
				departTime = timer + cDuration.peekFront();
			}
			else{
				cLine.enqueue(cTime.peekFront());
				cLineDuration.enqueue(cDuration.peekFront());
				lineLength++;
			}
			cTime.dequeue();
			cDuration.dequeue();
		}
		else{
			if(!cLine.isEmpty()){
				tmp = departTime - cLine.peekFront();
				totalWaitTime += tmp;
				if(tmp > maxWaitTime){
					maxWaitTime = tmp;
				}
				Teller = false;
				timer = departTime;
				departTime += cLineDuration.peekFront();
				lineLength--;
			}
			else{
				Teller = true;
			}
			cLine.dequeue();
			cLineDuration.dequeue();
		}
		if(maxLineLength < lineLength){
			maxLineLength = lineLength;
		}
	}

	simt = totalWaitTime; // Simulation time
	awt = totalWaitTime / numCustomers; // Average wait time
	mwt = maxWaitTime; // Maximum wait time
	twt = totalWaitTime / departTime; // Average line length
	mll = maxLineLength; // Max line length
	idt = idleTime; // Total idle time

	fin.close();
}

/*
@post Data is read in and the simulation has been run with one line and one teller
@param simt use to store how long the simulation takes
@param awt use to store how long the average waiting time is
@param mwt use to store the maximum waiting time
@param twt use to store the total wait time
@param mll use to store the max line length
@param ita use to store the idle teller 1 time
@param itb use to store the idle teller 2 time
@param itc use to store the idle teller 2 time
*/
void ThreeOne(float& simt, float& awt, float& mwt, float& twt, float& mll, float& ita, float& itb, float& itc){

	fstream fin;
	fin.open("data");

	LinkedQueue cTime, cDuration, cLine, cLineDuration;
	bool TA = true, TB = true, TC = true; // Teller is available
	float aDepartTime = 0, bDepartTime = 0, cDepartTime = 0; // Departure time for each
	float timerA = 0, timerB = 0, timerC = 0, currentTime = 0;
	float tmp = 0, totalWaitTime = 0, lineLength = 0, numCustomers = 0;
	float maxLineLength = 0, idleA = 0, idleB = 0, idleC = 0, maxWaitTime = 0;

	int aTime, aDur;
	while(!fin.eof()){
		fin >> aTime >> aDur;
		numCustomers++;
		cTime.enqueue(aTime);
		cDuration.enqueue(aDur);
	}

	while(!cTime.isEmpty() || !TA || !TB || !TC){
		if(!cTime.isEmpty() && ((TA && TB && TC) || (TA && TB && cTime.peekFront() < cDepartTime) || (TA && TC && cTime.peekFront() < bDepartTime) || (TB && TC && cTime.peekFront() < aDepartTime) ||
		(TA && cTime.peekFront() < bDepartTime && cTime.peekFront() < cDepartTime) || (TB && cTime.peekFront() < aDepartTime && cTime.peekFront() < cDepartTime) || (TC && cTime.peekFront() < aDepartTime && cTime.peekFront() < bDepartTime)
		|| (cTime.peekFront() < aDepartTime && cTime.peekFront() < bDepartTime && cTime.peekFront() < cDepartTime))){
			if(cLineDuration.isEmpty() && TA){
				idleA += cTime.peekFront() - aDepartTime;
			}
			if(cLineDuration.isEmpty() && TB){
				idleB += cTime.peekFront() - bDepartTime;
			}
			if(cLineDuration.isEmpty() && TC){
				idleC += cTime.peekFront() - cDepartTime;
			}
			if(TA){
				TA = false;
				timerA = cTime.peekFront();
				aDepartTime = timerA + cDuration.peekFront();
			}
			else if(TB){
				TB = false;
				timerB = cTime.peekFront();
				bDepartTime = timerB + cDuration.peekFront();
			}
			else if(TC){
				TC = false;
				timerC = cTime.peekFront();
				cDepartTime = timerC + cDuration.peekFront();
			}
			else{
				cLine.enqueue(cTime.peekFront());
				cLineDuration.enqueue(cDuration.peekFront());
				lineLength++;
			}
			cTime.dequeue();
			cDuration.dequeue();
		}
		else{
			if((!TA && TB && TC) || (!TA && TB && aDepartTime <= cDepartTime) || (!TA && TC && aDepartTime <= bDepartTime) || (!TA && aDepartTime <= bDepartTime && aDepartTime <= cDepartTime)){
				if(!cLine.isEmpty()){
					tmp = aDepartTime - cLine.peekFront();
					totalWaitTime += tmp;
					if(tmp > maxWaitTime){
						maxWaitTime = tmp;
					}
					TA = false;
					timerA = aDepartTime;
					aDepartTime += cLineDuration.peekFront();
				}
				else{
					TA = true;
				}
			}
			else if((TA && TC) || (!TB && TA && bDepartTime <= cDepartTime) || (!TB && TC && bDepartTime <= aDepartTime) || (!TB && bDepartTime <= aDepartTime && bDepartTime <= cDepartTime)){
				if(!cLine.isEmpty()){
					tmp = bDepartTime - cLine.peekFront();
					totalWaitTime += tmp;
					if(tmp > maxWaitTime){
						maxWaitTime = tmp;
					}
					TB = false;
					timerB = bDepartTime;
					bDepartTime += cLineDuration.peekFront();
				}
				else{
					TB = true;
				}
			}
			else{
				if(!cLine.isEmpty()){
					tmp = cDepartTime - cLine.peekFront();
					totalWaitTime += tmp;
					if(tmp > maxWaitTime){
						maxWaitTime = tmp;
					}
					TC = false;
					timerC = cDepartTime;
					cDepartTime += cLineDuration.peekFront();
				}
				else{
					TC = true;
				}
			}
			cLine.dequeue();
			cLineDuration.dequeue();
		}
		if(maxLineLength < lineLength){
			maxLineLength = lineLength;
		}
	}

	int departTime = aDepartTime;
	if(departTime < bDepartTime){
		departTime = bDepartTime;
	}
	if(departTime < cDepartTime){
		departTime = cDepartTime;
	}

	simt = totalWaitTime;
	awt = totalWaitTime / numCustomers;
	mwt =  maxWaitTime;
	twt = totalWaitTime / departTime;
	mll = maxLineLength;
	ita = idleA;
	itb = idleB;
	itc = idleC;

	fin.close();
}

/*
@post Data is read in and the simulation has been run with one line and one teller
@param simt use to store how long the simulation takes
@param awt use to store how long the average waiting time is
@param mwt use to store the maximum waiting time
@param twt use to store the total wait time
@param mll use to store the max line length
@param ita use to store the idle teller 1 time
@param itb use to store the idle teller 2 time
@param itc use to store the idle teller 2 time
*/
void ThreeThree(float& simt, float& awt, float& mwt, float& twt, float& mll, float& ita, float& itb, float& itc){
	fstream fin;
	fin.open("data2");

	LinkedQueue cTime, cDuration, cLineDuration;
	LinkedQueue lineA, lineAduration, lineB, lineBduration, lineC, lineCduration;
	float lengthA = 0, lengthB = 0, lengthC = 0;
	bool TA = true, TB = true, TC = true; // Teller is available
	float timerA = 0, timerB = 0, timerC = 0; // Keeps track of time for each teller
	float aDepartTime = 0, bDepartTime = 0, cDepartTime = 0; // Departure time for each
	float numCustomers = 0, tmp = 0, waitTimeA = 0, waitTimeB = 0, waitTimeC = 0;

	int aTime, aDur;
	while(!fin.eof()){
		fin >> aTime >> aDur;
		numCustomers++;
		cTime.enqueue(aTime);
		cDuration.enqueue(aDur);
	}

	while(!cTime.isEmpty() || !TA || !TB || !TC){
		if(!cTime.isEmpty() && ((TA && TB && TC) || (TA && TB && cTime.peekFront() < cDepartTime) || (TA && TC && cTime.peekFront() < bDepartTime) || (TB && TC && cTime.peekFront() < aDepartTime) ||
		(TA && cTime.peekFront() < bDepartTime && cTime.peekFront() < cDepartTime) || (TB && cTime.peekFront() < aDepartTime && cTime.peekFront() < cDepartTime) || (TC && cTime.peekFront() < aDepartTime && cTime.peekFront() < bDepartTime)
		|| (cTime.peekFront() < aDepartTime && cTime.peekFront() < bDepartTime && cTime.peekFront() < cDepartTime))){
			if(TA){
				TA = false;
				timerA = cTime.peekFront();
				aDepartTime = timerA + cDuration.peekFront();
			}
			else if(TB){
				TB = false;
				timerB = cTime.peekFront();
				bDepartTime = timerB + cDuration.peekFront();
			}
			else if(TC){
				TC = false;
				timerC = cTime.peekFront();
				cDepartTime = timerC + cDuration.peekFront();
			}
			else{
				if(lengthA <= lengthB && lengthA <= lengthC){
					lineA.enqueue(cTime.peekFront());
					lineAduration.enqueue(cDuration.peekFront());
					lengthA++;
				}
				else if(lengthB <= lengthA && lengthB <= lengthC){
					lineB.enqueue(cTime.peekFront());
					lineBduration.enqueue(cDuration.peekFront());
					lengthB++;
				}
				else{
					lineC.enqueue(cTime.peekFront());
					lineCduration.enqueue(cDuration.peekFront());
					lengthC++;
				}
			}
			cTime.dequeue();
			cDuration.dequeue();
		}
		else{
			if((!TA && TB && TC) || (!TA && TB && aDepartTime <= cDepartTime) || (!TA && TC && aDepartTime <= bDepartTime) || (!TA && aDepartTime <= bDepartTime && aDepartTime <= cDepartTime)){
				if(!lineA.isEmpty()){
					TA = false;
					timerA = aDepartTime;
					aDepartTime += lineAduration.peekFront();
				}
				else{
					TA = true;
				}
				lineA.dequeue();
				lineAduration.dequeue();
			}
			else if((TA && TC) || (!TB && TA && bDepartTime <= cDepartTime) || (!TB && TC && bDepartTime <= aDepartTime) || (!TB && bDepartTime <= aDepartTime && bDepartTime <= cDepartTime)){
				if(!lineB.isEmpty()){
					TB = false;
					timerB = bDepartTime;
					bDepartTime += lineBduration.peekFront();
				}
				else{
					TB = true;
				}
				lineB.dequeue();
				lineBduration.dequeue();
			}
			else{
				if(!lineC.isEmpty()){
					TC = false;
					timerC = cDepartTime;
					cDepartTime += lineCduration.peekFront();
				}
				else{
					TC = true;
				}
				lineC.dequeue();
				lineCduration.dequeue();
			}
		}
	}
}

/*
@post All three functions will be run twice, and data output to file
*/
int main(){
	float simt, awt, mwt, twt, mll, idA, idB, idC;
	clock_t timer;
	fstream fout;
	fout.open("Array"); // Change "Array" to "Node" when doing Node

	fout << "Simulation Time\tProcessing Time\tAverage Wait Time\tMax Wait Time\tAverage Line Length\tMax Line Length\tTotal Idle Time\n";
	for(int i = 0; i < 10; i++){
		timer = clock();
		OneOne(simt, awt, mwt, twt, mll, idA);
		timer = clock() - timer;
		fout << simt << '\t' << timer << '\t' << awt << '\t' << mwt << '\t' << twt << '\t' << mll << '\t' << idA << '\n';
	}
	fout << "Simulation Time\tProcessing Time\tAverage Wait Time\tMax Wait Time\tAverage Line Length\tMax Line Length\tTeller 1 Idle\tTeller 2 Idle\tTeller 3 Idle\n";
	for(int i = 0; i < 10; i++){
		timer = clock();
		ThreeOne(simt, awt, mwt, twt, mll, idA, idB, idC);
		timer = clock() - timer;
		fout << simt << '\t' << timer << '\t' << awt << '\t' << mwt << '\t' << twt << '\t' << mll << '\t' << idA << '\t' << idB << '\t' << idC << '\n';
	}
	
	fout << "Simulation Time\tProcessing Time\tAverage Wait Time\tMax Wait Time\tAverage Line Length\tMax Line Length\tTeller 1 Idle\tTeller 2 Idle\tTeller 3 Idle\n";
	for(int i = 0; i < 10; i++){
		timer = clock();
		ThreeThree(simt, awt, mwt, twt, mll, idA, idB, idC);
		timer = clock() - timer;
		fout << simt << '\t' << timer << '\t' << awt << '\t' << mwt << '\t' << twt << '\t' << mll << '\t' << idA << '\t' << idB << '\t' << idC << '\n';
	}

	return 0;
}