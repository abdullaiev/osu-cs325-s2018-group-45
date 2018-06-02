/*****************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 *
 * Implementation for the SolveTSP class
 * *********************/

#include <math.h>
#include <queue>


#include "SolveTSP.h"
#include "SpatialTree.h"
#include "Problem.h"

/**************************************
 * Constructor and Destructor
 * ************************************/

SolveTSP::SolveTSP(){

}

SolveTSP::~SolveTSP(){

}


/**************************************
 * Internal Functions
 * ************************************/

void SolveTSP::solve2OPT(std::string filename)
{
  Problem Prob(filename);
  std::vector<City> cities = Prob.getData();



}








/********
 * Input: 2 City Objects
 * Output: rounded integer value
 *
 * Description: Calculates the Euclidean Distance
 * 	between 2 City Objects and rounds to the 
 * 	nearest integer.
 * *****/
int SolveTSP::distance(City* A, City* B){
  double dist;
  dist = sqrt((B->xCoord-A->xCoord)^2 + (B->yCoord-A->yCoord)^2); 
  int roundDist = round(dist);
  return roundDist;
}


/******************
 *
 *  CALL TOUR CLASS TO INITIALIE TOUR 
 *
 *  NN IS NOW IMPLEMENTED IN TOUR CLASS NOT HERE
 *
 * ***************/


/********
 *
 *
 *
 * *****/

/**
void 2opt(Tour* tour, int size)
{
  bool improve;  // make sure improvments are being made. 
  int distanceNew;
  int distanceBest;
  // tourNew = tour by calling dupicate function


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

}	
**/










