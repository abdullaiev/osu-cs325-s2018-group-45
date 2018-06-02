/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the Node class
 ****************************************/
#include "Node.h"

// Sets this node and all children to not-visited
void Node::ClearVisited(bool percolate) {
	visited = false;
	if (percolate) {
		if (left)
			left->ClearVisited();
		if (right)
			right->ClearVisited();
	}
}

bool Node::AllVisited() const {
	if (left && !left->AllVisited())
		return false;
	if (right && !right->AllVisited())
		return false;
	return visited;
}