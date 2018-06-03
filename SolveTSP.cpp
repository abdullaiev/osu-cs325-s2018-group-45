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
  int improve = 0;  // make sure improvments are being made. 
 
 // Could set the loop to check for n number of iterations without an improvment then break.
 // EXAMPLE: while(improve < 15)  --> makes it at most check a neighborhood without any improvments
  for(int i=0; i<size-1; i++)
  {
    k=i+1;
    while(improve <15 && k<size)
    {
	if(2optSwap(tour, i, k))
	{
	  improve = 0;  //reset iteration back to 0
	}
	else
	{
	  improve++;  // not improved, so increase count.
	}
	k++;
    }
  }
  
}	
**/


/**
bool 2optSwap(Tour* tour, int i, int k)
{
  bool improveBool = FALSE;
  int D = 0; 
  int inc = 0;
  for(int s=i; s<=k; ++s)
  {
    D += distance(tour.getCity(s-1), tour.getCity(k-inc))
    inc++;
  }

  // Finds the current lenght of the section from i to k
  distanceCur = tourLength(tour.getCity(i), tour.getCity(k));

  if(D < distanceCur)
  {
    // redirect the cities to point to the new path above

    improveBool = TRUE; 
  }

  return improveBool;
}
**/


