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

Solution SolveTSP::solve2OPT(Problem problem) {

  
    // Nearest Neighbor currently returns a Solution, but when 2OPT is working
    // 		maybe have it return a tour so it can just then be fed right into 
    // 		the 2opt function call and if desired sent to a Solution Object (outside of solveNN)

//	Solution soln = solveNN(problem);
	
	int size = problem.getSize();
	
	cout << "solve2OPT: Problem size: " << size << endl;
	cout << "solve2OPT: Tour size: " << tour.size() << endl;
	TwoOpt(tour, size);
	
	int dist = 0;
	dist = SegmentLength(tour, 0, size-1) + tour[size-1]->DistanceTo(tour[0]);
	
	return Solution(dist, tour);



}

//This is not working
Solution SolveTSP::solveNN(Problem problem) {
    int size = problem.getSize();
    vector < City * > allCities = problem.getData();
//    vector < City * > tour;  // ILLIA, I made this tour vector a private variable for the class.
    tour.push_back(allCities.at(0));
    allCities.at(0)->visited = true;
    long totalDistance = 0;
    bool NOISY = false;

    if (NOISY) {
        cout << "Size: " << size << "\n";
    }

	// TESTING
	//size = 10;
	////////////
    for (int i = 0; i < size; i++) {
        int nearestNeighborDistance = -1;
        int nearestNeighborIndex = -1;

        if (NOISY) {
            cout << "Iteration: " << i << "\n";
        }

        for (int j = 0; j < size; j++) {
            if (i == j) {
                continue;
            }

            City * potentialNeighbor = allCities.at(j);

            if (NOISY) {
                cout << "potentialNeighbor: " << potentialNeighbor->id << ". Visited:  " << potentialNeighbor->visited << "\n";
            }

            if (potentialNeighbor->visited) {
                continue;
            }

            City * currentCity = allCities.at(i);
            int distanceToCity = currentCity->DistanceTo(potentialNeighbor);

            if (NOISY) {
                cout << "currentCity: " << currentCity->id << ". Distance to potential neighbor:  " << distanceToCity << "\n";
            }

            if (nearestNeighborDistance == -1 || nearestNeighborDistance > distanceToCity) {
                nearestNeighborDistance = distanceToCity;
                nearestNeighborIndex = j;
            }
        }

        if (nearestNeighborIndex != -1) {
            City *nextNeighbor = allCities.at(nearestNeighborIndex);
            nextNeighbor->visited = true;
            tour.push_back(nextNeighbor);
            totalDistance = totalDistance + nearestNeighborDistance;
			//cout << nearestNeighborDistance << ", ";

            if (NOISY) {
                cout << "Nearest neighbor index: " << nearestNeighborIndex << "\n";
                cout << "Nearest neighbor distance: " << nearestNeighborDistance << "\n";
                cout << "Running total: " << totalDistance << "\n";
            }
        }
    }

    /**** ALEX GARBAGE STUFF ****/
    // CAN DELETE, JUST TESTING
    bool status = verifyApprox(tour, size);
    if(status)
 	std::cout << "Distances are less than 25% different, GOOD TO GO" << std::endl;
    else
	std::cout << "Distances are greater than 25% difference, Change Starting Point." << std::endl; 

    // for alex debugging w/TwoOpt (sorry i am muddying up yor code)
    std::cout << "NN Total Distance: " << totalDistance << std::endl;
    int trial = SegmentLength(tour, 0, size-1);
    std::cout << "SEG LENGTH: " << trial << std::endl; 

    //TwoOpt(tour, size);



   /**** END OF ALEX GARBAGE STUFF ****/


    Solution solution(totalDistance, tour);
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
  for(int i=1; i<size-2; i++)
  {
    for(int k=i+1; k<size-1; k++)
    {
	// Swaps Edges and chooses the best path
	TwoOptSwap(tour, i, k);
    }
  }

 int dist2OPT = SegmentLength(tour, 0, size-1);
 int returnHome = tour[size-1]->DistanceTo(tour[0]); 
 std::cout << "TWO-OPT FINAL DISTANCE: " << dist2OPT+returnHome << std::endl; 
}	


// Switch the order of cities in an interval
void SolveTSP::ReverseTour(std::vector<City*>& tour, int i, int k) {
	while (i < k) {
		City* tmp = tour[i];
		tour[i] = tour[k];
		tour[k] = tmp;
		i++;
		k--;
	}
}

void SolveTSP::TwoOptSwap(std::vector<City*>& tour, int i, int k)
{
  // NOTE: CANNOT SWAP First and LAST ELEMENT (since they are starting and stopping points)
  // NOTE: Set Limits to never check below 0 and above (size-1) in Neighborhoods

  // Lengths of the current path segment and the swapped path segment
  int lengthCur = 0;
  int lengthSwap = 0;
  City* temp;   

  lengthCur = SegmentLength(tour, i-1, k+1);
  
  ReverseTour(tour, i, k);
  /*
  temp = tour[i];
  tour[i] = tour[k];
  tour[k] = temp;
  */

  lengthSwap = SegmentLength(tour, i-1, k+1);

  // If distance before the swap is less than after the swap, then revert back
  if(lengthCur < lengthSwap)
  {
	ReverseTour(tour, i, k);
    /*
	temp = tour[k];
    tour[k] = tour[i];
    tour[i] = temp;
	*/
  }
}


//Hmm maybe receive tour size so knows when to wrap around?
int SolveTSP::SegmentLength(const std::vector<City*>& tour, int i, int k)
{
  int A, B;
  int segmentLength = 0;
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
	//if (i == 0 && k == tour.size() -1)
		//std::cout << tour[z]->DistanceTo(tour[z+1]) << ", ";
  }

  return segmentLength;
}




