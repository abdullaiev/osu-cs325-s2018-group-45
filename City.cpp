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

City::City(int id, int x, int y) {
	this->id = id;
	this->xCoord = x;
	this->yCoord = y;
};

string City::ToString() {
	return "City " + to_string(id) + ": (" + to_string(xCoord) + ", " + to_string(yCoord) + ")";
	
};

bool City::CompareX(const City* lhs, const City* rhs){
	return lhs->xCoord < rhs->xCoord;
}

bool City::CompareY(const City* lhs, const City* rhs){
	return lhs->yCoord < rhs->yCoord;
}

bool City::CompareID(const City* lhs, const City* rhs){
	return lhs->id < rhs->id;
}