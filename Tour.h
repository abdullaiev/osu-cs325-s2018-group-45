/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the Tour class
 ****************************************/
#ifndef CS325_GRP45_TOUR_H
#define CS325_GRP45_TOUR_H

#include <vector>
#include <queue>

#include "City.h"

using std::vector;
using std::queue;

class Tour {
private:
	vector<City*> cities;
	int size;

public:
	Tour(vector<City*> cities);
	
	// Get info about a city by index, including adjacent cities or visited flag
	City* GetCity(int index) const;
	queue<City*> GetNearest(int index, int count) const;
	bool IsVisited(int index) const;
	int Count() const;
};

#endif