/**
  * @file PA03.cpp
  *
  * @brief Put the FlightMap implementation to use
  * @details Main file for project. Will call upon functions to
  * read in data and generate a flight path.
  *
  * @version 1.00
  *		Wei Tong (18 October 2016)
  *		Turned in version and initial development
  *
  * @note
  *		Adapted from Frank M. Carrano and Timothy M. Henry
  *		Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */

#include "FlightMap.v1.cpp"
#include "FlightMap.v2.cpp"

int main(){

	string str1 = "cityFile.txt";
	string str2 = "flightFile.txt";
	Map Derp;
	Derp.readFlightMap(str1, str2);
	Derp.test("Denton", "Los Angeles");

	return 0;
}