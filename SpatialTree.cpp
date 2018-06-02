/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the SpatialTree class
 ****************************************/
#include <vector>
#include <queue>
#include <algorithm>

#include "SpatialTree.h"

using std::vector;
using std::queue;
using std::sort;

SpatialTree::SpatialTree() {
	size = 0;
	root = NULL;
}
// Build a tree from a list of cities.
// Cities are sorted and split by alternating x/y
SpatialTree::SpatialTree(vector<City*> cities) {
	size = cities.size();
	
	// Make a copy of the cities list for sorting in place
	/*if size < 1 {
		root = NULL;
	} else {
		
	}*/
	;
};

bool SpatialTree::AllVisited() const {
	return root && root->AllVisited();
}

void SpatialTree::ClearVisited() {
	if (root)
		root->ClearVisited();
};

City* SpatialTree::GetNextNearest(City* city) {
	return NULL;
};

queue<City*> SpatialTree::GetKNearest(City* city, int k) {
	return queue<City*>();
};

const int SpatialTree::Count() {
	return size;
}