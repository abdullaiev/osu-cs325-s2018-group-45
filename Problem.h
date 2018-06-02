/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Interface for the Problem class
 ****************************************/
#ifndef OSU_CS325_S2018_GROUP_45_PROBLEM_H
#define OSU_CS325_S2018_GROUP_45_PROBLEM_H

#include <string>
#include "City.h"

using std::string;

class Problem {
private:
    City * cities;

public:
    Problem(string inputFileName);
    City * getData();
};

#endif //OSU_CS325_S2018_GROUP_45_PROBLEM_H
