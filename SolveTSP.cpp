/*****************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 *
 * Implementation for the SolveTSP class
 * *********************/

#include <math.h>
#include <queue>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "SolveTSP.h"
#include "SpatialTree.h"
#include "Problem.h"

using std::vector;
using std::cout;
using std::endl;

/***********************************
IDEAS

1) Handle wrap-around for dist calcs and edge swaps
2) Use long for all dist sums
3) Don't reverse nodes from i to k unless swap took place
4) Use nearest neighbor to instead of all k nodes
   - perhaps checking selecting others as well
5) Run 2-OPT more than once?
6) Figure out why size and getSize() are not the same. Perhaps this is why the dist calcs difference
7) Rerun NN tour builder with different random nodes?
************************************/




/**************************************
 * Constructor and Destructor
 * ************************************/

SolveTSP::SolveTSP() {

}

SolveTSP::~SolveTSP() {

}


/**************************************
 * Internal Functions
 * ************************************/
/* Going to Serve as the main solve function that brings together the solution */

Solution SolveTSP::solve(Problem problem) {


    // Nearest Neighbor currently returns a Solution, but when 2OPT is working
    // 		maybe have it return a tour so it can just then be fed right into
    // 		the 2opt function call and if desired sent to a Solution Object (outside of solveNN)

	Solution soln = solveNN(problem);

	int size = problem.getSize();

	cout << "solve: Problem size: " << size << endl;
	cout << "solve: Tour size: " << tour.size() << endl;
	TwoOpt(tour, size);

	long dist = 0;
	dist = SegmentLength(tour, 0, size-1) + tour[size-1]->DistanceTo(tour[0]);

	return Solution(dist, tour);



}

//This function solves a TSP by using the Nearest Neighbor approach.
//It starts from a random vertex, marks it as visited, and then finds the next nearest vertex until all vertices have been visited.
Solution SolveTSP::solveNN(Problem problem) {
    int size = problem.getSize();
    vector <City *> allCities = problem.getData();
    bool NOISY = true;

    //If City Size is less than 500, run more times for better accuracy.
    int ATTEMPTS = size < 500 ? 20 : 5;
    
    vector <City *> currentTour;
    long shortestDistance = -1;
    long currentDistance = 0;

    if (NOISY) {
        cout << "Running NN algorithm on a problem of size " << size << "...\n";
    }

    //We've discovered that running NN multiple times starting from different random vertices can yield a shorter overall path.
    for (int count = 0; count < ATTEMPTS; count++) {
        //Clear all variables for this iteration
        currentTour.clear();
        currentDistance = 0;
        for (int i = 0; i < size; i++) {
            allCities.at(i)->visited = false;
        }

        //Start the tour from a random vertex, mark it as visited
        int randomIndex = std::rand() % size;  //calls srand() in Main.cpp
        City * currentCity = allCities.at(randomIndex);
        currentTour.push_back(currentCity);
        currentCity->visited = true;

        if (NOISY) {
            cout << "Iteration " << count << ". Starting with a random vertex at index " << randomIndex << ".\n";
        }

        bool allVisited = false;

        //Keep on finding next nearest neighbors until all vertices have been visited
        while (!allVisited) {
            allVisited = true;

            int nextNeighborDistance = -1;
            City * nextNeighbor;

            for (int j = 0; j < size; j++) {
                if (allCities.at(j)->visited) {
                    continue;
                } else {
                    //There are still neighbors not visited
                    allVisited = false;

                    //Get distance to the next potential neighbor
                    City * neighbor = allCities.at(j);
                    int distance = currentCity->DistanceTo(neighbor);

                    //If this neighbor is closer to the current city than any other, save it's distance
                    if (nextNeighborDistance == -1 || distance < nextNeighborDistance) {
                        nextNeighborDistance = distance;
                        nextNeighbor = neighbor;
                    }
                }
            }

            //Add the nearest neighbor found in the loop above to the tour
            if (nextNeighborDistance != -1) {
                nextNeighbor->visited = true;
                currentTour.push_back(nextNeighbor);
                currentCity = nextNeighbor;
                currentDistance = currentDistance + nextNeighborDistance;
            }
        }

        if (NOISY) {
            cout << "Iteration " << count << " resulted in shortest distance of " << currentDistance << ".\n";
        }

        //Once the tour is constructed, check if it shorter than any previously calculates tours
        if (shortestDistance == -1 || currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            this->tour = currentTour;
        }
    }

    cout << "NN finished. Final shortest distance: " << shortestDistance << ". Double check tour size: " << this->tour.size() << ".\n";
    //cout << "Verifying Distance by going through Array(not counting return to start): " << SegmentLength(tour, 0,this->tour.size()-1) << std::endl;
    Solution solution(shortestDistance, this->tour);
    return solution;
}

/******************
 * Verifies that the approximation made by NN is somewhat accurate
 * 	by checking the first few lenghts vs the last few lengths.
 * 	If lengths are greater than 25% different, then may want to 
 * 	choose a different starting point for NN
 *
 * ***************/

bool SolveTSP::verifyApprox(const std::vector<City*>& tour, int size)
{
  bool check = true; //for debugging
  bool verify = false;
  int lengthBeg = 0;
  int lengthEnd = 0;
  int approxAve = 0;
 

  // Note: sizes under 10 will be run with the Exact Solution
  if(size > 10)
  {
    for(int i=0; i<3; i++)
    {    
	lengthBeg += tour[i]->DistanceTo(tour[i+1]);
    }
    for(int i=size-1; i>size-4; i--)
    {
	lengthEnd += tour[i]->DistanceTo(tour[i-1]);
    }
    
    // Verifies that the percentage difference is under 25 
    approxAve = abs(lengthBeg-lengthEnd)/((lengthEnd+lengthBeg)/2)*100;

    if(check){
    	std::cout << "Beginning Lenght: " << lengthBeg << std::endl;
    	std::cout << "Ending Length: " << lengthEnd << std::endl;
    	std::cout << "Percentage: " << approxAve << std::endl;
    }


    if(approxAve < 25)
    {
	verify = true;
    }

  }

  else {verify = true;}

  return verify;
}



/*************   2-OPT IMPLEMENTATION **************/


void SolveTSP::TwoOpt(std::vector<City*>& tour, int size)
{

  int improve =0;
  int count = 0;
 
  // Used for Control on larger problems.  Only check neighbhorhood of 
  if(size <= 500)
  {
    count = size;
  } 
  else
  { 
    count = 500;
  }

  
  // Keep Tyring to improve 2-OPT algorithm until improve value is reached...meh
  while(improve <10){
    for(int i=0; i<size-1; i++)
    {
	// Following For Loops do not create the wrap around indices, that is done in TwoOptSwap
	// Swap with elements behind 
	for(int k=1; k<count; k++)
	{
	  TwoOptSwap(tour, i, i+k, size);
	}     
	
	// Swap with elements ahead(only need this for counts>500?
      /**
      if(count >500)
      {
	for(int k=1; k<count; k++)
	{
	  TwoOptSwap(tour, i, i-k, size);
	}
      }
      **/
    }
 
    // Display the Final Calculated Distance by 2-OPT, while also considering the distance home
    long dist2OPT = SegmentLength(tour, 0, size-1);
    long returnHome = tour[size-1]->DistanceTo(tour[0]);
    long distTotal = dist2OPT +returnHome;
    std::cout << "TWO-OPT FINAL DISTANCE: " << distTotal << std::endl;
     
    improve++;
  } //while loopy
}


/******************
 * SWAPS and COMPARES EDGES
 *
 *
 * ***************/
void SolveTSP::TwoOptSwap(std::vector<City*>& tour, int i, int k, int size)
{

  // Lengths of the current path segment and the swapped path segment
  long lengthCur = 0;
  long lengthSwp = 0;

  // Making sure indices can wrap around 
  if(k<0)
  {
    k = (size-1)+k;
  }
  else if(k > (size-1))
  {
    k = k-(size-1)-1;
  }
  
  
  // Handles Edge Cases:
  int k1, i1;
  if(k == size-1)
	k1 = 0;
  else
	k1 = k+1;

  if(i == 0)
	i1 = size-1;
  else
	i1 = i-1;

  lengthCur = (tour[i1]->DistanceTo(tour[i])) + (tour[k]->DistanceTo(tour[k1]));
  lengthSwp = (tour[i1]->DistanceTo(tour[k])) + (tour[i]->DistanceTo(tour[k1]));

  // If Edges before the swap are greater than after the potnetial swap, then perform the actual swap
  if(lengthCur > lengthSwp)
  {
	//std::cout << "--- CALLING REVERSE ---" << std::endl;
	ReverseTour(tour, i, k, size);
  }
}



// Switch the order of cities in an interval

void SolveTSP::ReverseTour(std::vector<City*>& tour, int i, int k, int size) {
  //NOTE: Need to have two separate reverses (i is beginning, k is ending):
  //	1. i<k aka beg < end  then normal reverse
  //	2. i>k aka beg > end then we know it wrapped around. 


  // CASE 1 (i<k) : Beginning is less than ending.
  if(i<k)
  {
	while (i < k) {
		//std::cout << "  ___ REVERSED___" << std::endl;
		City* tmp = tour[i];
		tour[i] = tour[k];
		tour[k] = tmp;
		i++;
		k--;
	}
  }

  // Case 2 (i>k) : Beginning is larger than Ending (so it wraps around).
  else if(i>k)
  {
    int steps = (size - abs(k-i))/2;
    for(int z=0; z<steps; z++)
    {
	City* tmp = tour[i];
	tour[i] = tour[k];
	tour[k] = tmp;
	i++;
	k--;
	ReverseUtil(i, k, size);
    }
  }

}


/***** ReverseUtil ******/
void SolveTSP::ReverseUtil(int &i, int &k, int size)
{
  // Make Indices Wrap Around
  if(k<0)
  {
    k = (size-1)+k;
  }
  else
    k = k;

  if(i>(size-1))
  {
    i = i-size;  //or i-(size-1)-1;
  }
  else
    i = i;

}



//Hmm maybe receive tour size so knows when to wrap around?
int SolveTSP::SegmentLength(const std::vector<City*>& tour, int i, int k)
{
  int A, B;
  long segmentLength = 0;
  if(i<k)
  {
    A = i;
    B = k;
  } 
  else
  {
    A = k;
    B = i;
  }

  // NEED TO THINK ABOUT EDGE CASE OF WRAPPING AROUND VECTOR..
  for(int z=A; z<B; z++)
  {
    segmentLength += tour[z]->DistanceTo(tour[z+1]);
    //std::cout << tour.at(z)->id <<" to " << tour.at(z+1)->id <<" Distance: " << segmentLength << std::endl;
  }

  return segmentLength;
}




