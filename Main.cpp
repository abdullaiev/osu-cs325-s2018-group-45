#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <stdlib.h>

#include "Node.h"
#include "City.h"
#include "Problem.h"
#include "SolveTSP.h"
#include "Solution.h"
#include "TSPExactSolver.h"

using std::endl;
using std::cout;
using std::vector;
using std::sort;
using std::string;
using std::cout;
using std::cin;


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
