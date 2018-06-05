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

// Represents a continuous path of connected cities
// Provides for getting a city or its neighbors by index
class Tour {
private:
    vector<City *> cities;
    int size;

public:
    // Guesses an initial tour, connecting the cities
    Tour(vector<City *> cities);

    // Get a city and an arbitrary index. Not path order related
    City *GetCity(int index) const;

    // Return the specified number of nearest neighbor cities, limited by the total number of cities
    queue<City *> GetNearest(int index, int count) const;

    bool IsVisited(int index) const;

    int Count() const;
};

#endif