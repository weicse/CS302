/**
  * @file FlightMap.v1.cpp
  *
  * @brief Find flight path for cities
  *
  * @details Three files are read in, and stored into a
  * node list. A flight path from one city to another is
  * then found using the stack.
  *
  * @version 1.00
  *		Wei Tong (18 October 2016)
  *		Turned in version and initial development
  *
  * @note
  *		Adapted from Frank M. Carrano and Timothy M. Henry
  *		Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */

#include <iostream>
#include <fstream>
using namespace std;

/** City class that stores inputted cities
  * @post The ADT is created with default values
  */
class City{
public:
	string cityName; // Name of the city
	bool visited; // If city has been visited during flight planning
	City* next; // Next city in linked list
	City* prev; // Previous city in linked list
	City* adjData; // Cities adjacent to this city
	friend class Map; // So Map can access data easily
};

class Pair{ // Relatively useless class.
	/** Read in a pair of city names
	  * 
	  * @pre A line of text is stored in the file
	  *
	  * @post Only the names of the first two city are taken
	  * in as strings.
	  * @param first The string to store the first city name
	  * @param second The string to store the second city name
	  * @param readIn The ifstream to read from the file
	  */
	void getNamePair(string& first, string& second, ifstream& readIn){
		char tmp3; // Store the comma after the name of the first city
		string tmp4; // Store everything after the name of the 2nd city
		getline(readIn, first, ','); // Read until comma
		readIn.get(tmp3); // Read in the comma
		getline(readIn, second, '	'); // Read until tab
		getline(readIn, tmp4); // Read in the rest of the line
	}
	/** Reads in a single name on a line from a file
	  *
	  * @pre A line contains a single city name
	  *
	  * @post The name is read into a string from the file
	  *
	  * @param cityName The string to store the city name
	  * @param readIn The ifstream to read from the file
	  */
	void getName(string& cityName, ifstream& readIn){
		getline(readIn, cityName);
	}
	friend class Map;
};

class Map{
public:
	City *cityData = NULL, *cdMove = NULL, *cdSet = NULL;
	City *fMove = NULL, *adMove = NULL;
	Pair ezReading; // Honestly what is the point of this function????
	/** Read in the data from the files
	  *
	  * @pre Three files with data inside them
	  *
	  * @post The data from the three files are read into stacks
	  *
	  * @param inputCity String of the name of the first input file
	  * @param inputFLight String of the name of the second input file
	  *
	  * @note The third read in file has not been implemented yet.
	  */
	void readFlightMap(string inputCity, string inputFlight){
		ifstream fin;
		fin.open(inputCity.c_str());
		while(!fin.eof()){
			if(cityData == NULL){
				cityData = new City();
				cdMove = cityData;
				cdMove->prev = NULL;
			}
			else{
				cdMove->next = new City();
				cdSet = cdMove->next;
				cdSet->prev = cdMove;
				cdMove = cdSet;
			}
			cdMove->adjData = NULL;
			cdMove->next = NULL;
			cdMove->visited = false;
			ezReading.getName(cdMove->cityName, fin);
		}
		fin.close();
		fin.open(inputFlight.c_str());
		while(!fin.eof()){
			string tmp1, tmp2;
			City *baseCity, *adjCity;
			ezReading.getNamePair(tmp1, tmp2, fin);
			cdMove = cityData;
			while(cdMove != NULL && cdMove->cityName != tmp1){
				cdMove = cdMove->next;
			}
			baseCity = cdMove;
			cdMove = cityData;
			while(cdMove != NULL && cdMove->cityName != tmp2){
				cdMove = cdMove->next;
			}
			adjCity = cdMove;
			insertAdjacent(*baseCity, *adjCity);
		}
		fin.close();
	}
	/** Display all the flights
	  *
	  * @post A list of all the flights is outputted to terminal
	  */
	void displayFlightMap(){
		cdMove = cityData;
		while(cdMove != NULL){
			if(cdMove->adjData != NULL){
				cdSet = cdMove->adjData;
				while(cdSet != NULL){
					cout << "Flight from " << cdMove->cityName << " to " << cdSet->cityName << endl;
					cdSet = cdSet->next;
				}
			}
			cdMove = cdMove->next;
		}

	}
	/** Displays a list of all the cities HPAir is affiliated with
	  *
	  * @post A list of all the cities HPAir is affiliated with is
	  * outputted to the terminal
	  *
	  */
	void displayAllCities(){
		cdMove = cityData;
		while(cdMove != NULL){
			cout << cdMove->cityName << endl;
			// Why does this require endl?
			// For some reason it gets overwritten if I don't endl
			cdMove = cdMove->next;
		}
	}
	/** Displays a list of all the cities adjacent to the city
	  *
	  * @post A list of all the cities that are adjacent to the
	  * current city
	  *
	  */
	void displayAdjacentCities(City aCity){
		cdMove = aCity.adjData;
		while(cdMove != NULL){
			cout << cdMove->cityName << endl;
			cdMove = cdMove->next;
		}
	}
	/** Marks a city as visited
	  *
	  * @post A city is marked as visited
	  *
	  */
	void markVisited(City &aCity){
		aCity.visited = true;
	}
	/** Marks all cities as unvisited
	  *
	  * @post All cities are now unvisited.
	  */
	void unvisitAll(){
		cdMove = cityData;
		while(cdMove != NULL){
			cdMove->visited = false;
			cdMove = cdMove->next;
		}
	}
	/** Check if a city has been visited
	  *
	  * @post A city is known to have/have not been visited
	  *
	  * @return A bool determining if the city has been visited
	  */
	bool isVisited(City aCity){
		if(aCity.visited){
			return true;
		}
		else{
			return false;
		}
	}
	/** Inserts a city adjacent to another city
	  *
	  * @post A city is created in the aCity's stack adjData
	  *
	  * @param aCity The city to have an adjacent city placed next to it
	  * @param adjCity The city adjacent to aCity
	  */
	void insertAdjacent(City& aCity, City adjCity){
		adMove = aCity.adjData;
		if(adMove == NULL){
			aCity.adjData = new City();
			adMove = aCity.adjData;
			aCity.adjData->prev = NULL;
		}
		else{
			while(adMove->next != NULL){
				adMove = adMove->next;
			}
			adMove->next = new City();
			cdSet = adMove->next;
			cdSet->prev = adMove;
			adMove = cdSet;
		}
		adMove->adjData = NULL;
		adMove->next = NULL;
		adMove->visited = false;
		adMove->cityName = adjCity.cityName;
	}
	/** Finds the next city to fly to
	  *
	  * @post Finds the next city in the flight, returning if no
	  * flights work, or the destination has been reached.
	  *
	  * @param aCityName The city the find the next flight from
	  */
	void getNextCity(string aCityName){
		City *tmp;
		cdMove = cityData;
		while(cdMove->cityName != aCityName && cdMove != NULL){
			cdMove = cdMove->next;
		}
		if(cdMove->adjData == NULL){
			if(fMove->prev == false && fMove->next == false){
				fMove = NULL;
				return;
			}
			pop();
			return;
		}
		else if(cdMove->adjData->visited == true){
			cdMove->adjData = cdMove->adjData->next;
			if(cdMove->adjData == NULL){
				pop();
				return;
			}
			else{
				push(*(cdMove->adjData));
				return;
			}
		}
		else{
			push(*(cdMove->adjData));
			return;
		}
	}
	/** Calls on other functions to create a flight path
	  *
	  * @post Outputs whether HPAir flies from one city to another
	  *
	  * @param originCity The original city to fly from
	  * @param destinationCity The destination to fly to
	  *
	  * @return A bool signalling if a flight path was successfully generated
	  */
	bool isPath(City &originCity, City &destinationCity){
		cout << "Request is to fly from " << originCity.cityName << " to " << destinationCity.cityName << endl;
		bool success;
		while(pop()); // Clear the stack
		unvisitAll();
		fMove = new City();
		fMove->prev = NULL;
		fMove->next = NULL;
		originCity.visited = true;
		fMove->cityName = originCity.cityName;
		while(fMove && fMove->cityName != destinationCity.cityName){
			getNextCity(fMove->cityName);
		}
		if(fMove == NULL){
			cout << "Sorry. HPAir does not fly from " << originCity.cityName << " to " << destinationCity.cityName << endl;
			return false;
		}
		else{
			cout << "HPAir flies from " << originCity.cityName <<" to " << fMove->cityName << endl;
			return true;
		}
	}
	/** Removes the first node in the stack
	  *
	  * @post A node is removed if the stack is not empty
	  *
	  * @return A bool signalling if the stack is empty or not
	  */
	bool pop(){
		if(fMove == NULL){
			return false;
		}
		else{
			fMove = fMove->prev;
			delete fMove->next;
			fMove->next = NULL;
			return true;
		}
	}
	/** Pushes a city into the stack
	  *
	  * @post The stack has a new node. First node is created as necessary
	  *
	  */
	void push(City &aCity){
		fMove->next = new City();
		City* ctmp = fMove->next;
		ctmp->prev = fMove;
		fMove = ctmp;
		fMove->cityName = aCity.cityName;
		fMove->next = NULL;
		fMove->adjData = NULL;
		markVisited(aCity);
	}
	/** Function to test flight between two cities without reading in data from 3rd file
	  *
	  * @post Flight path is generated if possible.
	  *
	  */
	void test(string str1, string str2){
		cdMove = cityData;
		while(cdMove->cityName != str1 && cdMove->next != NULL){
			cdMove = cdMove->next;
		}
		if(cdMove->cityName != str1){
			cout << str1 << " - " << cdMove->cityName << endl;
			cout << "City DNE...1" << endl;
			return;
		}
		else{
			cdSet = cityData;
			while(cdSet->cityName != str2 && cdSet->next != NULL){
				cdSet = cdSet->next;
			}
			if(cdSet->cityName != str2){
				cout << "City DNE...2" << endl;
				return;
			}
			else{
				isPath(*cdMove, *cdSet);
				return;
			}
		}
	}
};