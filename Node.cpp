/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the Node class
 ****************************************/
#include "Node.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::sort;

SpatialNode::SpatialNode() {
	left = NULL; 
	right = NULL; 
	city = NULL; 
	visited = false;
};

SpatialNode::SpatialNode(City* city) {
	left = NULL;
	right = NULL;
	this->city = city;
	visited = false;
};

// Sorts the cities by X or Y, takes the median city, and recursively builds the tree on either side 
SpatialNode::SpatialNode(City* cities[], int iMin, int iMax, SplitDim dim) {
	visited = false;
	left = right = NULL;
	splitDim = dim;
	
	if (iMin >= iMax - 1) {
		city = cities[iMin];
	} else {
		int iMed = (iMin + iMax) / 2;
		
		// Order by smallest to largest x or y coordinate and switch dim for child node construction
		if (dim == SPLIT_X) {
			sort(cities + iMin, cities + iMax, City::CompareX);
			dim = SPLIT_Y;
		} else {
			sort(cities + iMin, cities + iMax, City::CompareY);
			dim = SPLIT_X;
		}
		
		// Assign the median city as this node's city. Then build left and right
		city = cities[iMed];
		if (iMin <= iMed)
			left  = new SpatialNode(cities, iMin, iMed, dim); 
		if (iMed <= iMax)
			right = new SpatialNode(cities, iMed + 1, iMax, dim);
	}
}

// Recursively deletes child nodes before self-deletion
SpatialNode::~SpatialNode() {
	if (left)
		delete left;
	if (right)
		delete right;
}

// Return the nearest neighbor to the given node that hasn't been visited
// If the left tree contains the city, the left-most of the right tree must be checked since it could be closer
// Same for the right tree
City* SpatialNode::GetNextNearest(const City* city) {
	int thisVal;
	int thatVal;
	
	// Select the correct coordinate for sorting at this level
	if (splitDim == SPLIT_X) {
		thisVal = this->city->xCoord;
		thatVal = city->xCoord;
	} else {
		thisVal = this->city->yCoord;
		thatVal = city->yCoord;
	}

	// Check if it belongs in the left subtree
	if (thatVal < thisVal) {
		// Get the nearest of the left subtree and compare it to the left-most of the right
		if (left && !left->visited) {
			return left->GetNextNearest(city);
		} else if (right && !right->visited) {
			return right->GetNextNearest(city);
		}
	// Its in the right subtree
	} else {
		if (right && !right->visited) {
			return right->GetNextNearest(city);
		} else if (left && !left->visited) {
			return left->GetNextNearest(city);
		}
	}
	visited = true;
	return this->city;
}

// Sets this node and all children to not-visited
void SpatialNode::ClearVisited(bool percolate) {
	visited = false;
	if (percolate) {
		if (left)
			left->ClearVisited();
		if (right)
			right->ClearVisited();
	}
}

bool SpatialNode::AllVisited() const {
	if (left && !left->AllVisited())
		return false;
	if (right && !right->AllVisited())
		return false;
	return visited;
}

void SpatialNode::Print() const {
	if (left) 
		left->Print();

	cout << string(4 * (Depth() - 1), ' ') << city->ToString() << endl;
	
	if (right)
		right->Print();
}

int SpatialNode::Depth() const {
	if (left and right){
		if (left->Depth() > right->Depth())
			return left->Depth() + 1;
		else
			return right->Depth() + 1;
	} else if (left){
		return left->Depth() + 1;
	} else if (right) {
		return right->Depth() + 1;
	} else {
		return 1;
	}
}
