/*****************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 *
 * Implementation for the SolveTSP class
 * *********************/

#include <math.h>

#include "SolveTSP.h"
#include "SpatialTree.h"


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
  // Grab a starting City from the Spatial Tree
  SpatialTree tree;
  
  
  // Add City to tour (make sure city nodes are pointing to null)
  
  // While(tree.AllVisitied())
  
	// GetNextNearest
	// Add city to tour
	
  // Point End of back to the beginning
  

};


/********
 *
 *
 *
 * *****/
void 2opt(Tour* tour, int size, Tour* tourNew)
{
  bool improve;  // make sure improvments are being made. 
  int distanceNew;
  int distanceBest;
  // tourNew = tour by calling dupicate function

/**
 // Could set the loop to check for n number of iterations without an improvment then break.
 // EXAMPLE: while(improve < 15)  --> makes it at most check a neighborhood without any improvments
  while(improve){
    improve = FALSE;
    bestDistance = tour.getLength();
    for(int i=0; i<size-1; i++)
    {
	for(int k=i+1; k<size; k++)
	{
	  2optSwap(tour, tourNew, i, k);
	  distanceNew = tourNew.getLength();
    
    	  if(distanceNew < bestDistance)
    	  {
	    tour = tourNew; 
	    distanceBest = distanceNew;
	    improve = TRUE;
    	  }

  	}
    }
  }  //end of while
	
**/



};






