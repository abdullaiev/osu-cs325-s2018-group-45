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
}

#endif