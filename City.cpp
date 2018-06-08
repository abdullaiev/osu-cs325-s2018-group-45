/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the City class
 ****************************************/
#include <string>
#include <math.h>

#include "City.h"

using std::string;
using std::to_string;


City::City(int id, int x, int y) {
    this->id = id;
    this->xCoord = x;
    this->yCoord = y;
    this->visited = false;
}

string City::ToString() {
	return /*"City " + to_string(id) + ": */"(" + to_string(xCoord) + ", " + to_string(yCoord) + ")";
	
}
int City::DistanceTo(const City *city) {
    int xDiff = this->xCoord - city->xCoord;
    int yDiff = this->yCoord - city->yCoord;
    float dist = sqrt(xDiff * xDiff + yDiff * yDiff);
    int distRound = round(dist);
    return distRound;
}
