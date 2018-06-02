/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the Node class
 ****************************************/
#include "Node.h"

#include <iostream>

using std::cout;
using std::endl;

Node::Node() {
	left = NULL; 
	right = NULL; 
	city = NULL; 
	visited = false;
};

Node::Node(City* city) {
	left = NULL;
	right = NULL;
	this->city = city;
	visited = false;
};

Node::~Node() {
	if (left)
		delete left;
	if (right)
		delete right;
}
	
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

void Node::Print() const {
	if (left)
		left->Print();
		
	cout << city->ToString() << endl;
	
	if (right)
		right->Print();
}