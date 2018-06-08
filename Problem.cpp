/***********************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Implementation for the Problem class.
 * Represents a TSP problem as an array of cities
 * read in from a text file in a specific format
 **********************************************/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include "City.h"
#include "Problem.h"

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::istream_iterator;
using std::cout;

// Reads in the problem definition from a file containing one line for 
// each city, with the ID, x and y listed in that order. The problem 
// class owns the memory storing the city objects.  It should be passed
// by reference because we didn't implement a copy constructor. 
// Deleting the problem will delete the cities from the heap.
Problem::Problem(string inputFileName) {
    bool status = true;
    vector < City * > cities;
    this->cities = cities;
    ifstream input(inputFileName);

    // Verify file was found and can be accessed
    if (input) {
        std::cout << inputFileName << " - Opened Successfully." << std::endl;
        std::cout << " CALCULATING SOLUTION... " << std::endl;  // since some run times may be long, lets user know
    } else {
        std::cout << inputFileName << " - could NOT access file." << std::endl;
        status = false;
    }

    if (status == true) {
        //Read input file line by line
        for (string line; getline(input, line);) {
            //Split each line into tokens delimited by a space
            istringstream buf(line);
            istream_iterator <string> beg(buf), end;
            vector <string> tokens(beg, end);

            //First token is city ID, second token is X coordinate, and the third token is Y coordinate.
            //Convert all values from string to integers
            int id = stoi(tokens.at(0));
            int x = stoi(tokens.at(1));
            int y = stoi(tokens.at(2));

            //Create a city object and add it to the array of cities for later usage
            City *city = new City(id, x, y);
            this->cities.push_back(city);
        }
    }
}

// Free up the memory allocated for storing cities
Problem::~Problem() {
	for (int i = 0; i < this->cities.size(); ++i) {
		if (cities[i])
			delete cities[i];
	}
}

// Returns a copy of the array of pointers to cities. The actually city 
// data is not duplicated to a new memory location
vector<City *> Problem::getData() const {
    return this->cities;
}

int Problem::getSize() const {
    return this->cities.size();
}
