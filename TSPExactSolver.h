/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Interface for the TSPExactSolver class
 ****************************************/

#ifndef OSU_CS325_S2018_GROUP_45_TSPEXACTSOLVER_H
#define OSU_CS325_S2018_GROUP_45_TSPEXACTSOLVER_H

#include <string>

#include "Solution.h"
#include "Problem.h"

using std::string;

class TSPExactSolver {
public:
    Solution solve(Problem problem);
};

#endif //OSU_CS325_S2018_GROUP_45_TSPEXACTSOLVER_H
