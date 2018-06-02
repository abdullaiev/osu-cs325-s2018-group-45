/********************************
 * Group 45
 * CS 325 - Spring 2018 
 *
 * Interface for SolveTSP class
 *
 * ********************************/

#ifndef SOLVETSP_H
#define SOLVETSP_H

#include <string>
#include <vector>
#include "City.h"
//#include "Tour.h"
#include "Node.h"

class SolveTSP{

  private:
	std::vector<City> cities;

  public:

	// Constructor and Destructor
	SolveTSP();
	~SolveTSP();

	// called in Main.cpp
	void solve2OPT(std::string);   // going to call Problem and then solve using NN and 2-opt

	int distance(City* A, City* B);		// Calculates Distance between City A and City B
	
//	void 2opt(Tour*, int);		// Receives a Complete Tour, # of cities in tour.
//	bool 2optSwap(Tour*, int, int);

	
	
};

#endif





