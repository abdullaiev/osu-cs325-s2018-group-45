/*****************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the SolveTSP class.  Performs
 * 	Nearest Neighbor and 2-OPT alogirthms to
 * 	find the shortest distance for the TSP Problem.
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

/**************************************
 * SolveTSP Class Constructor and Destructor
 * ************************************/

SolveTSP::SolveTSP() {

}

SolveTSP::~SolveTSP() {

}

/***************************************
 * Description: Solves the TSP Problem by parsing the data into a tree,
 * 	Running Nearest Neighbor multiple times and choosing the best,
 * 	Send the best tour result from Nearest Neighbor to the 2-OPT
 * 	Algorithm, which runs until it converges on a value, and finally
 * 	writes the results to a file.
 *
 * ************************************/
/* Going to Serve as the main solve function that brings together the solution */
Solution SolveTSP::solve(Problem problem) {

  int n = 0;
  bool sizeCheck = true;  //checks the size of the input to determine how many loops

  // Max iterations of 10, but will be less depending on the input size
  while(n <10)
  {
    // Clear the current tour and Run Nearest Neighbor 
    tour.clear();
    Solution nnSolution = solveNN(problem);
    int size = problem.getSize();

    //cout << "solve: Problem size: " << size << endl;
    //cout << "solve: Tour size: " << tour.size() << endl;

    // Run 2-Opt Algorithm
    TwoOpt(tour, size);

    // Find the total distance(though a bit redundant since it calcs in 2-opt..)
    distanceCur = 0;
    distanceCur = SegmentLength(tour, 0, size - 1) + tour[size - 1]->DistanceTo(tour[0]);

    // Set the first iteration equal to the best tour and distance
    if(n == 0)
    {
	distanceBest = distanceCur;
	tourBest = tour;
    }

    // Loop Control: Check the input Size and set the number of loops accordingly
    if(sizeCheck)
    {
	if(size > 2001 && size < 5001){
	  n = 5;
	  sizeCheck = false;
	}
	else if(size > 5001){
	  n = 7;
	  sizeCheck = false;
	}
	else{
	  sizeCheck = false;
	}
    }
    
    // If the current implementation is a shorter distance, then keep it. 
    if(distanceCur < distanceBest)
    {
	distanceBest = distanceCur;
	tourBest = tour;
    }

    n++;
  }

  std::cout << "FINAL DISTANCE: " << distanceBest << std::endl;
  return Solution(distanceBest, tourBest);
}


/**************************************
 * Description: Neartest Neighbor Algorithm.  Starts from a Random 
 * 	Vertex, marks it as a visited, and then finds the next
 * 	nearest vertex until all teh vertices have been visited.
 *
 * ***********************************/

Solution SolveTSP::solveNN(Problem problem) {
    int size = problem.getSize();
    vector < City * > allCities = problem.getData();
    bool NOISY = false;

    //If City Size is less than 500, run more times for better accuracy.
    int ATTEMPTS = size < 500 ? 20 : 5;

    vector < City * > currentTour;
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
        City *currentCity = allCities.at(randomIndex);
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
            City *nextNeighbor;

            for (int j = 0; j < size; j++) {
                if (allCities.at(j)->visited) {
                    continue;
                } else {
                    //There are still neighbors not visited
                    allVisited = false;

                    //Get distance to the next potential neighbor
                    City *neighbor = allCities.at(j);
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

    //cout << "NN finished. Final shortest distance: " << shortestDistance << ". Double check tour size: "
    //     << this->tour.size() << ".\n";
    Solution solution(shortestDistance, this->tour);
    return solution;
}


/**************************************
 * Description: 2-OPT Algorithm, a specific type of K-OPT,
 * 	that rearranges 2 edges to see if the swap produces
 * 	a better result.  If it does, then the swap is 
 * 	made.
 *
 * Internal Function Calls:
 * 	- TwoOptSwap
 * 	- SegmentLength
 *
 * ***********************************/
void SolveTSP::TwoOpt(vector<City*>& tour, int size) {
    bool improve = true;
    int count = 0;
    int distancePrev = 0;
    // Used for Control on larger problems.  Only check neighbhorhood of
    if (size <= 2000) {
        count = size;
    } else {
        count = 2000;
    }

    // Keep Tyring to improve 2-OPT algorithm until it no longer converges (previous distance = current distance)
    while (improve) {
        for (int i = 1; i < size - 2; i++) {
            // Compare Edges and swap if yielding a better result
            for (int k = 1; k < count - 1; k++) {
                TwoOptSwap(tour, i, i + k, size);
            }
        }

        // Display the Final Calculated Distance by 2-OPT, while also considering the distance home
        long dist2OPT = SegmentLength(tour, 0, size - 1);
        long returnHome = tour[size - 1]->DistanceTo(tour[0]);
        long distTotal = dist2OPT + returnHome;
        //cout << "TWO-OPT FINAL DISTANCE: " << distTotal << std::endl;
	if(distancePrev == distTotal){
	  improve = false;
	}
	else{
	  distancePrev = distTotal;
	}
    }
}


/**************************************
 * Description: Compares 2 edges, if being swapped in the tour
 * 	yields a shorter distance, then the swap is performed on
 * 	the main tour.
 * 	 
 *  Internal Function Calls: 
 *  	- ReverseTour
 * ************************************/
void SolveTSP::TwoOptSwap(vector<City*>& tour, int i, int k, int size) {
    // Lengths of the current path segment and the swapped path segment
    long lengthCur = 0;
    long lengthSwp = 0;

    // Making sure indices can wrap around the vector
    if (k < 0) {
        k = (size - 1) + k;
    } else if (k > (size - 1)) {
        k = k - (size - 1) - 1;
    }

    // Handles the Edge Cases:
    int k1, i1;
    if (k == size - 1)
        k1 = 0;
    else
        k1 = k + 1;

    if (i == 0)
        i1 = size - 1;
    else
        i1 = i - 1;

    // Adds together 2 edges for the current config & if edges were swapped.
    lengthCur = (tour[i1]->DistanceTo(tour[i])) + (tour[k]->DistanceTo(tour[k1]));
    lengthSwp = (tour[i1]->DistanceTo(tour[k])) + (tour[i]->DistanceTo(tour[k1]));

    // If Edges before the swap are greater than after the potnetial swap, then perform the actual swap
    if (lengthCur > lengthSwp) {
        ReverseTour(tour, i, k, size);
    }
}


/**************************************
 * Description: Reverses the path travelled
 * 	within a tour. 
 *
 * Note: Sensative to the order of passed in variables. 
 * 	i and k are NOT interchangeable, but are the 
 * 	starting and ending points of the section to be
 * 	reversed.  DOES handle wrap around cases. 
 *
 * ***********************************/
void SolveTSP::ReverseTour(vector<City*>& tour, int i, int k, int size) {
    //NOTE: Need to have two separate reverses (i is beginning, k is ending):
    //	1. i<k aka beg < end  then normal reverse
    //	2. i>k aka beg > end then we know it wrapped around.

    // CASE 1 (i<k) : Beginning is less than ending.
    if (i < k) {
        while (i < k) {
            //cout << "  ___ REVERSED___" << std::endl;
            City *tmp = tour[i];
            tour[i] = tour[k];
            tour[k] = tmp;
            i++;
            k--;
        }
    }

    // Case 2 (i>k) : Beginning is larger than Ending (so it wraps around).
    else if (i > k) {
        int steps = (size - abs(k - i)) / 2;
        for (int z = 0; z <= steps; z++) {
            City *tmp = tour[i];
            tour[i] = tour[k];
            tour[k] = tmp;
            i++;
            k--;
            ReverseUtil(i, k, size);
        }
    }
}


/**************************************
 * Description: Takes care of any indices that
 * 	go out of the vector bounds by wrapping
 * 	them around.
 *
 * Note: This Utility Function only handles cases where
 * 	k is always decrementing and i is always
 * 	incrementing.
 *
 * ***********************************/
void SolveTSP::ReverseUtil(int &i, int &k, int size) {
    // Make Indices Wrap Around

    // Valid only when k is decrementing
    if (k < 0) {
        k = size + k;
    } else {
        k = k;
    }
  
    // Valid only when i is incrementing
    if (i > (size - 1)) {
        i = i - size;  
    } else {
        i = i;
    }
}


/**************************************
 * Description: Calculates the total distance between
 * 	2 endpoints. This implementation handles undirected
 * 	graphs that do NOT wrap around.  Will always take
 * 	the smallest value and make it the starting point. 
 *
 * ***********************************/
int SolveTSP::SegmentLength(const vector<City*>& tour, int i, int k) {
    int A, B;
    long segmentLength = 0;

    // Always chooses the the smallest value as the starting point.
    if (i < k) {
        A = i;
        B = k;
    } else {
        A = k;
        B = i;
    }

    // Adding the segment of the vector that was passed in.   
    for (int z = A; z < B; z++) {
        segmentLength += tour[z]->DistanceTo(tour[z + 1]);
        //cout << tour.at(z)->id <<" to " << tour.at(z+1)->id <<" Distance: " << segmentLength << std::endl;
    }

    return segmentLength;
}

