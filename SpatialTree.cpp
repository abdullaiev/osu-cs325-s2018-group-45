/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the SpatialTree class
 ****************************************/
#include <vector>
#include <queue>
#include "SpatialTree.h"

using std::vector;
using std::queue;

SpatialTree::SpatialTree(vector<City*> cities) {
	root = NULL;
};

void SpatialTree::ClearVisited() {
};

City* SpatialTree::GetNextNearest(City* city) {
	return NULL;
};

queue<City*> SpatialTree::GetKNearest(City* city, int k) {
	return queue<City*>();
};