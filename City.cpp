/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the City class
 ****************************************/
#include "City.h"

#include <string>
using std::string;
using std::to_string;

City::CompareMethod City::compareBy = CMP_ID;

City::City(int id, int x, int y) {
	this->id = id;
	this->xCoord = x;
	this->yCoord = y;
};

string City::ToString() {
	return "City " + to_string(id) + ": (" + to_string(xCoord) + ", " + to_string(yCoord) + ")";
	
};

bool City::operator < (const City& other) const {
	if (this->compareBy == CMP_X)
		return this->xCoord < other.xCoord;
	else if (this->compareBy == CMP_Y)
		return this->yCoord < other.yCoord;
	else
		return this->id < other.id;
}

bool City::Compare(const City* lhs, const City* rhs) {
	return *lhs < *rhs;
}