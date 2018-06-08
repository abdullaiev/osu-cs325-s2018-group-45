/***********************************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Description:
 *
 * Solves a TSP problem specified in a file, a path
 * to which is provided as the only argument.
 * An exact or appx solver is used, depending on the problem
 * size and the solution is written to an output file.
 * *********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <stdlib.h>

#include "City.h"
#include "Problem.h"
#include "Solution.h"
#include "SolveTSP.h"
#include "TSPExactSolver.h"

using std::endl;
using std::cout;
using std::vector;
using std::sort;
using std::string;
using std::cout;
using std::cin;

// The only argument (excluding the program argument) is the problem definition
// file path. The user is prompted to manually enter the file path if none is provided.
// The solution file is the input file name with '.tour' appended.
// The exact solver is used for problems under 10 cities, otherwise the appx solver is used.
int main(int argc, char *argv[]) {
    string inputFileName;
    string outputFileName;

    if (argc == 1) {
        cout << "Please enter the filename: ";
        cin >> inputFileName;
    } else {
        inputFileName = argv[1];
    }

    outputFileName = inputFileName + ".tour";

    //Measure algorithm performance
    clock_t start = clock();

    //Parse the input file and create a TSP
    Problem tsp(inputFileName);

    //Use the exact algorithm for small size problems
    if (tsp.getSize() < 10) {
        TSPExactSolver exactTSP;
        exactTSP.solve(tsp).write(outputFileName);
    } else {
        //Use Nearest Neighbor + 2-OPT for bigger problems
        srand(time(NULL));
        SolveTSP solveTSP;
        solveTSP.solve(tsp).write(outputFileName);
    }

    //Print execution time
    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.2lf seconds.\n", duration);

    return 0;
}
