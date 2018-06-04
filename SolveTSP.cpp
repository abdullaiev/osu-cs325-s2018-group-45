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



/********
 * Input: 2 City Objects
 * Output: rounded integer value
 *
 * Description: Calculates the Euclidean Distance
 * 	between 2 City Objects and rounds to the 
 * 	nearest integer.
 * *****/
int SolveTSP::distance(City *A, City *B) {
    double dist;
    dist = sqrt((B->xCoord - A->xCoord) ^ 2 + (B->yCoord - A->yCoord) ^ 2);
    int roundDist = round(dist);
    return roundDist;
}


/*************   2-OPT IMPLEMENTATION **************/


void SolveTSP::TwoOpt(std::vector<City*>& tour, int size)
{
  //int improve = 0;  // make sure improvments are being made. 

  // NOTE: This Implementation never changes the starting city so skips over index 0  
  // NOTE: Need to Create a limit Iterator (check +-10 city neighborhood)
 int count =0;
 while(count <5){
  for(int i=1; i<size-1; i++)
  {
    for(int k=i+1; k<size; k++)
    {
	// Swaps Edges and chooses the best path
	TwoOptSwap(tour, i, k, size);
    }
  }
 
 long dist2OPT = SegmentLength(tour, 0, size-1);
 long returnHome = tour[size-1]->DistanceTo(tour[0]);
 std::cout << "TWO-OPT FINAL DISTANCE: " << dist2OPT+returnHome << std::endl; 

 count++;
 } //inner while loopy
}


// Switch the order of cities in an interval
void SolveTSP::ReverseTour(std::vector<City*>& tour, int i, int k) {

  if(i>k)
  {
    int temp = i;
    i = k;
    k = temp;
  }

	while (i < k) {
		City* tmp = tour[i];
		tour[i] = tour[k];
		tour[k] = tmp;
		i++;
		k--;
	}
}


/******************
 * SWAPS and COMPARES EDGES
 *
 *
 * ***************/
void SolveTSP::TwoOptSwap(std::vector<City*>& tour, int i, int k, int size)
{
  // NOTE: CANNOT SWAP First and LAST ELEMENT (since they are starting and stopping points)
  // NOTE: Set Limits to never check below 0 and above (size-1) in Neighborhoods

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


 // ONLY Check check edges being switched..
  lengthCur = (tour[i-1]->DistanceTo(tour[i])) + (tour[k]->DistanceTo(tour[k+1]));
  lengthSwp = (tour[i-1]->DistanceTo(tour[k])) + (tour[i]->DistanceTo(tour[k+1]));

  // If distance before the swap is less than after the swap, then revert back
  if(lengthCur > lengthSwp)
  {
	ReverseTour(tour, i, k);
  }
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
   // std::cout << tour.at(z)->id <<" to " << tour.at(z+1)->id <<" Distance: " << segmentLength << std::endl;
  }

  return segmentLength;
}




