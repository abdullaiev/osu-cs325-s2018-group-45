/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the SpatialTree class
 ****************************************/
#ifndef CS325_GRP45_SPATIAL_TREE_H
#define CS325_GRP45_SPATIAL_TREE_H

#include <vector>
#include <queue>
#include "Node.h"
#include "City.h"

using std::vector;
using std::queue;

// Represents a 2-d tree of spatial sorted cities for use
// in nearest neighbor selections
class SpatialTree {
private:
	Node* root;
	int size;
public:
	SpatialTree(vector<City*> cities);
	void ClearVisited();
	City* GetNextNearest(City* city);
	queue<City*> GetKNearest(City* city, int k);
	int Count();
};

#endif