/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Interface for the Node
 ****************************************/
#ifndef CS325_GRP45_NODE_H
#define CS325_GRP45_NODE_H

#include "City.h"

// Represents a tree or path node representing a city 
class Node {
public:
	Node* left; 
	Node* right;
	City* city;
	bool visited;
	
	Node();
	Node(City* city);
	~Node();
	
	// Clears the visited flag for the node (and its children if percolate is true)
	void ClearVisited(bool percolate=true);
	bool AllVisited() const;
	
	void Print() const;
};

#endif
