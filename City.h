/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the City class
 ****************************************/
#ifndef CS325_GRP45_CITY_H
#define CS325_GRP45_CITY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

// Represents a location in the x,y plane 
// with an identifying #
class City {


public:
    int id;
    int xCoord;
    int yCoord;
    City *next;
    City *prev;
    bool visited;

    City(int id, int x, int y);

    string ToString();

public:
    static bool CompareX(const City *lhs, const City *rhs);

    static bool CompareY(const City *lhs, const City *rhs);

    static bool CompareID(const City *lhs, const City *rhs);

    int DistanceTo(const City *city);
};


// Comparators for sorting in different ways
#endif
