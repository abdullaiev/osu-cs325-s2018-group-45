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

using std::cout;
using std::endl;
using std::string;
using std::vector;

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

// Populate the node with cities 
SpatialNode::SpatialNode(vector<City*> cities, SplitDim dim) {
	left = NULL;
	right = NULL;
	city = NULL;
	visited = false;
}

SpatialNode::~SpatialNode() {
	if (left)
		delete left;
	if (right)
		delete right;
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

int SpatialNode::Print(int offset) const {
	if (left) {
		offset = left->Print(offset);
		offset += 2;
	}

	cout << string(offset, ' ') << city->ToString() << endl;
	
	if (right) {
		offset -= 2;
		offset = right->Print(offset);
		offset += 2;
	}
	return offset;
}

	
