/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Interface for the Solution class
 ****************************************/

#ifndef OSU_CS325_S2018_GROUP_45_SOLUTION_H
#define OSU_CS325_S2018_GROUP_45_SOLUTION_H

#include <string>

using std::string;

class Solution {
private:
    long distance;
    City * tour;

public:
    Solution(int distance, City * tour);
    void write(string fileName);
};

#endif //OSU_CS325_S2018_GROUP_45_SOLUTION_H
