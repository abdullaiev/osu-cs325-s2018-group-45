/****************************************
 * Group 45
 * CS 325 - Spring 2018
 *
 * Implementation for the TSPExactSolver class
 ****************************************/

#include <iostream>
#include <algorithm>
#include <vector>

#include "TSPExactSolver.h"
#include "Solution.h"
#include "Problem.h"

using std::cout;
using std::vector;
using std::next_permutation;


//This function solves the TSP with a brute force approach. It generates all permutations of the vertices in the graph
//and finds the one the yields a path with the minimum distance.
//Danger: This functions runs in O(n!) time and should not be used for inputs with 10 or more vertices.
Solution TSPExactSolver::solve(Problem problem) {
    int size = problem.getSize();
    int * indices;
    indices = new int[size];
    int * shortestTour;
    shortestTour = new int[size];
    int shortestDistance = -1;
    bool NOISY = false;

    //Do not attempt to solve TSP if the number of vertices is less than two
    if (size < 2) {
        Solution solution(0, problem.getData());
        return solution;
    }

    //Initialize the array of indices so it can be used for generation of all indices permutations
    for (int i = 0; i < size; i++) {
        indices[i] = i;
    }

    //Check the path length for every permutation of the vertices
    do {
        int total = 0;
        for (int j = 1; j < size; j++) {
            City city1 = problem.getData().at(indices[j]);
            City city2 = problem.getData().at(indices[j - 1]);
            int distance = city1.DistanceTo(&city2);
            total = total + distance;

            if (NOISY == true) {
                cout << "Distance from " << indices[j] << " to " << indices[j-1] << " is " << distance << "\n";
            }
        }

        if (NOISY == true) {
            cout << "Distance: " << total << ". Permutation: " << indices[0] << indices[1] << indices[2] << indices[3] << '\n';
        }

        //If current permutation results in a shorter path than we already have, store it's distance and the sequence of vertices
        if (total < shortestDistance || shortestDistance == -1) {
            shortestDistance = total;
            for (int k = 0; k < size; k++) {
                shortestTour[k] = indices[k];
            }
        }
    } while (next_permutation(indices, indices+size));

    //Construct an array of cities based on the stored indices of the shortest path
    vector<City> shortestPath;
    for (int n = 0; n < size; n++) {
        City city = problem.getData().at(shortestTour[n]);
        shortestPath.push_back(city);
    }

    Solution solution(shortestDistance, shortestPath);
    return solution;
}
