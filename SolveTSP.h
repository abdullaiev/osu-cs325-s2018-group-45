/********************************
 * Group 45
 * CS 325 - Spring 2018 
 *
 * Interface for SolveTSP class
 *
 * ********************************/

#ifndef SOLVETSP_H
#define SOLVETSP_H


#include "City.h"
#include "Tour.h"
#include "Node.h"

class SolveTSP{

  private:
	Tour* tour;		// Empty Tour Object to store the inital tour
	Tour* tourNew;		// Empty Tour Object to store the updating approx tour..

  public:

	// Constructor and Destructor
	SolveTSP();
	~SolveTSP();

	// Internal Functions run:  *NOTE: maybe make private
	int distance(City* A, City* B);		// Calculates Distance between City A and City B
	void duplicateTour(Tour*, Tour*);	// Makes a copy of a tour.

	void NN(Tour*);				// Receives a blank Tour and Fills it in
	void 2opt(Tour*, int, Tour*);		// Receives a Complete Tour, # of cities in tour, and an empty tour.


	// User Interface Functions:

	
};

#endif





