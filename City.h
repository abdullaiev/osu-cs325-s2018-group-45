/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the City class
 ****************************************/
#ifndef CS325_GRP45_CITY_H
#define CS325_GRP45_CITY_H

#include <string>
using std::string;

// Represents a location in the x,y plane 
// with an identifying #
class City {
public:
	int id; 
	int xCoord;
	int yCoord;
	
	City(int id, int x, int y);
	string ToString();
};

#endif