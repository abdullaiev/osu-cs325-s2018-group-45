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
#include "Solution.h"
#include "Problem.h"


class SolveTSP {

private:
    std::vector <City*> tour;	// Will hold the final tour.  Used in NN and TwoOpt

public:

    // Constructor and Destructor
    SolveTSP();

    ~SolveTSP();

    // called in Main.cpp
    Solution solve(Problem problem);   // going to call Problem and then solve using NN and 2-opt
    Solution solveNN(Problem problem);

    bool verifyApprox(const std::vector<City*>&, int);
    int distance(City *A, City *B);        // Calculates Distance between City A and City B

    void TwoOpt(std::vector<City*>&, int);		// Receives a Complete Tour, # of cities in tour.
    void TwoOptSwap(std::vector<City*>&, int, int);
    int SegmentLength(const std::vector<City*>&, int, int);

private:
	void ReverseTour(std::vector<City*>& tour, int i, int k);
};

#endif





