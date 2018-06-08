/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Interface for the Problem class
 * Represents a TSP problem as an array of cities
 * read in from a text file in a specific format
 ****************************************/
#ifndef OSU_CS325_S2018_GROUP_45_PROBLEM_H
#define OSU_CS325_S2018_GROUP_45_PROBLEM_H

#include <string>
#include <vector>
#include "City.h"

using std::string;
using std::vector;

class Problem {
private:
    vector<City *> cities;

public:
	// Reads problem file and stores pointers to the cities data in an array
    Problem(string inputFileName);
	// Frees the cities from memory
	~Problem();
	// Returns a copy of the pointers only
    vector<City *> getData() const;

    int getSize() const;
};

#endif //OSU_CS325_S2018_GROUP_45_PROBLEM_H
