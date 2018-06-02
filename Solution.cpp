/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Implementation for the Solution class
 ****************************************/

#include "Solution.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

Solution::Solution(int distance, vector <City> tour) {
    this->distance = distance;
    this->tour = tour;
}

void Solution::write(string fileName) {
    //todo
}
