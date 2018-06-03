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

enum SplitDim {SPLIT_X, SPLIT_Y};

// Represents a tree or path node representing a city 
class SpatialNode {
public:
	SpatialNode* left; 
	SpatialNode* right;
	City* city;
	bool visited;
	SplitDim splitDim;
	
	SpatialNode();
	// Create an orphaned node with the given city
	SpatialNode(City* city);
	// Populate the left and right nodes with cities 
	// Sorts the array IN-PLACE!
	SpatialNode(City* cities[], int iMin, int iMax, SplitDim dim);
	
	~SpatialNode();
	
	//
	City* GetNextNearest(const City* city);
	
	// Clears the visited flag for the node (and its children if percolate is true)
	void ClearVisited(bool percolate=true);
	bool AllVisited() const;
	
	// Returns the offset that was used for this node
	void Print() const;
	int Depth() const;
	
private:
	SpatialNode* GetLeftNearest();
	SpatialNode* GetRightNearest();
};

#endif
