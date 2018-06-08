/**********************************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the City class
 * Represents an x,y location with a unique integer
 * ID and directed connectivity to two neighboring cities.
 **********************************************************/
#ifndef CS325_GRP45_CITY_H
#define CS325_GRP45_CITY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

// Represents a location in the x,y plane 
// with an identifying #. Also has pointers to neighboring cities
class City {
public:
	int id; 
	int xCoord;
	int yCoord;
	City* next;
	City* prev;
	bool visited;
	
	City(int id, int x, int y);
	string ToString();

    int DistanceTo(const City *city);
};


// Comparators for sorting in different ways
#endif
