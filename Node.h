/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the Node
 ****************************************/
#ifndef CS325_GRP45_NODE_H
#define CS325_GRP45_NODE_H

#include <string>
#include <vector>
#include "City.h"

using std::string;
using std::vector;

// Represents a tree or path node representing a city 
class SpatialNode {
public:
	enum SplitDim {SPLIT_X, SPLIT_Y};

	SpatialNode* left; 
	SpatialNode* right;
	City* city;
	bool visited;
	SplitDim splitdim;
	
	SpatialNode();
	// Create an orphaned node with the given city
	SpatialNode(City* city);
	// Populate the node with cities 
	SpatialNode(vector<City*> cities, SplitDim dim);
	~SpatialNode();
	
	// Clears the visited flag for the node (and its children if percolate is true)
	void ClearVisited(bool percolate=true);
	bool AllVisited() const;
	
	// Returns the offset that was used for this node
	int Print(int offset=0) const;
};

#endif
