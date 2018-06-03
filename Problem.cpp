/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Implementation for the Problem class
 ****************************************/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include "City.h"
#include "Problem.h"

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::istream_iterator;
using std::cout;

Problem::Problem(string inputFileName) {
    bool status = true;
    vector<City *> cities;
    this->cities = cities;
    ifstream input(inputFileName);

  // Verify file was found and can be accessed
  if(input){
    std::cout << inputFileName <<" - Opened Successfully." << std::endl;
  }

  else{
    std::cout << inputFileName << " - could NOT access file." << std::endl;
    status = false;
  }

  if(status == true)
  {
    //Read input file line by line
    for(string line; getline(input, line);) {
        //Split each line into tokens delimited by a space
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        //First token is city ID, second token is X coordinate, and the third token is Y coordinate.
        //Convert all values from string to integers
        int id = stoi(tokens.at(0));
        int x = stoi(tokens.at(1));
        int y = stoi(tokens.at(2));

        //Create a city object and add it to the array of cities for later usage
        City * city = new City(id, x, y);
        this->cities.push_back(city);
    }
  }
}

vector<City *> Problem::getData() {
    return this->cities;
}

int Problem::getSize() {
    return this->cities.size();
}
