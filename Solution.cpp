/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Implementation for the Solution class
 ****************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Solution.h"

using std::string;
using std::vector;
using std::ofstream;
using std::cout;

Solution::Solution(int distance, vector <City> tour) {
    this->distance = distance;
    this->tour = tour;
}

void Solution::write(string fileName) {
    //Open the output file by given name
    ofstream outputFile(fileName);
    cout << "Saving the solution to " << fileName << "\n";

    if (outputFile.is_open()) {
        //Write the optimal distance first
        outputFile << this->distance;
        outputFile << "\n";

        //Then write the sequence of the cities that make a TS tour
        for (City &city : this->tour) {
            outputFile << city.id;
            outputFile << "\n";
        }

        outputFile.close();
    }
}
