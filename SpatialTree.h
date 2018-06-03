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
	SpatialNode* root;
	int size;
public:
	SpatialTree();
	SpatialTree(const vector<City*> cities);
	~SpatialTree();
	
	bool AllVisited() const;
	void ClearVisited();
	queue<City*> GetKNearest(const City* city, int k);
	int Count() const;
	int Depth() const;
	
	void Print() const;
};

#endif