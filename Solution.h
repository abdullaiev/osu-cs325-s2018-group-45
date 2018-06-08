/**********************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Interface for the Solution class
 **********************************************/

#ifndef OSU_CS325_S2018_GROUP_45_SOLUTION_H
#define OSU_CS325_S2018_GROUP_45_SOLUTION_H

#include <string>
#include <vector>
#include "City.h"

using std::string;
using std::vector;

/* 
 * Represents an optimal tour, including the
 * tour length and an array of cities, the order
 * of which defines the adjacency.
 */
class Solution {
private:
    long distance;
    vector<City *> tour;

public:
    Solution(long distance, vector<City *> tour);

	// Output the solution to a file in the required format.
	// Outputs total distance and the tour defined as a sequence
	// of city IDs
    void write(string fileName);
};

#endif //OSU_CS325_S2018_GROUP_45_SOLUTION_H
