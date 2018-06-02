/*****************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 *
 * Implementation for the SolveTSP class
 * *********************/

#include <math.h>

#include "SolveTSP.h"

/**************************************
 * Constructor and Destructor
 * ************************************/

SolveTSP::SolveTSP(){

};

SolveTSP::~SolveTSP(){

};

/**************************************
 * Internal Functions
 * ************************************/

/********
 * Input: 2 City Objects
 * Output: rounded integer value
 *
 * Description: Calculates the Euclidean Distance
 * 	between 2 City Objects and rounds to the 
 * 	nearest integer.
 * *****/
int SolveTSP::distance(City* A, City* B){
  int dist;
  dist = round(((B.x-A.x)^2 + (B.y-A.y)^2)^0.5) 

  return dist;
};

/********
 * Input: Pointer to a Tour Object
 * Output: Nothing
 * 
 * Description: Receives an empty Tour Object and
 * 	performs Nearest Neighbor Algorithm
 * 	using a Spatial Tree.... 
 * *****/

void SolveTSP::NN(Tour* tour){



};


/********
 *
 *
 *
 * *****/
void 2opt(Tour* tour, int size, Tour* tourNew)
{



};






