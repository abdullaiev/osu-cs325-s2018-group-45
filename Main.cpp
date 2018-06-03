#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>

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
/**
	vector<City*> cities;
	
	cities.push_back(new City(5, 5, 1));
	cities.push_back(new City(4, 3, 3));
	cities.push_back(new City(3, 1, 2));
	cities.push_back(new City(2, 2, 5));
	cities.push_back(new City(1, 4, 4));
	
	sort(cities.begin(), cities.end(), City::CompareID);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
	sort(cities.begin(), cities.end(), City::CompareX);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
		sort(cities.begin(), cities.end(), City::CompareY);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;

**/

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
    if (tsp.getSize() <= 10) {
        TSPExactSolver exactTSP;
        exactTSP.solve(tsp).write(outputFileName);
    } else {
//        SolveTSP solveTSP;
//        solveTSP.solve2OPT(inputFileName);
    }

    //Print execution time
    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.2lf seconds.\n", duration);

    return 0;
}
