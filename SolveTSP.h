/********************************
 * Group 45
 * CS 325 - Spring 2018 
 *
 * Interface for SolveTSP class.  Calls a function to Parse 
 * 	an input file and then implements Nearest Neighbor 
 * 	and 2-OPT Algorithms to solve the TSP Problem.
 * 	Finally sends the data to Solutions class to 
 * 	write the results to a file.
 *
 * ********************************/

#ifndef SOLVETSP_H
#define SOLVETSP_H

#include <string>
#include <vector>

#include "City.h"
#include "Solution.h"
#include "Problem.h"


class SolveTSP {

private:
    std::vector<City *> tour;  					// Holds the final tour(used in NN and TwoOpt)
    std::vector<City *> tourBest;
    long distanceCur;
    long distanceBest;
public:

    // Constructor and Destructor
    SolveTSP();
    ~SolveTSP();

    // called in Main.cpp
    Solution solve(const Problem& problem);   				// Calls Problem and solves using NN and 2-opt

    // Internal Functions
    Solution solveNN(const Problem& problem);				// Performs the Nearest Neighbor Algorithm
    void TwoOpt(std::vector<City *> &, int);        		// Performs the 2-OPT Algorithm
    void TwoOptSwap(std::vector<City *> &, int, int, int);	// Swaps 2 Edges and Checks if the path is shorter
    int SegmentLength(const std::vector<City *> &, int, int);	// Returns Distance of a path

private:
    void ReverseTour(std::vector<City *> &tour, int i, int k, int size);

    void ReverseUtil(int &, int &, int);
};

#endif





