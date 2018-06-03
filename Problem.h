/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Interface for the Problem class
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
    vector<City> cities;

public:
    Problem(string inputFileName);
    vector<City> getData();
    int getSize();
};

#endif //OSU_CS325_S2018_GROUP_45_PROBLEM_H
