/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the SpatialTree class
 ****************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#include "SpatialTree.h"

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::sort;
using std::string;

/*void DumbTree(vector<City*> cities) {
	if (cities.size() < 1)
		return NULL;

	for (int i = 0; i < cities.size(); ++i)
		
}*/

SpatialTree::SpatialTree() {
    size = 0;
    root = NULL;

}

// Build a tree from a list of cities.
// Cities are sorted and split by alternating x/y
SpatialTree::SpatialTree(const vector<City *> cities) {
    size = cities.size();

    // Avoid changing the order of the original list of cities
    vector < City * > citiesCopy = cities;

    // Must have at least 1 city
    if (size < 1) {
        cout << "No cities. Setting root to NULL..." << endl;
        root = NULL;
    }
        // Recursively build the tree
    else {
        cout << "Building root node..." << endl;
        root = new SpatialNode(citiesCopy.data(), 0, size, SPLIT_X);
    }
} // Had ; here

SpatialTree::~SpatialTree() {
    if (root)
        delete root;
}

bool SpatialTree::AllVisited() const {
    return root && root->AllVisited();
}

void SpatialTree::ClearVisited() {
    if (root)
        root->ClearVisited();
} // Had ; here

queue<City *> SpatialTree::GetKNearest(const City *city, int k) {
    // Limit to the number of nodes available
    if (k >= size)
        k = size - 1;

    queue < City * > q;

    ClearVisited();
    for (int i = 0; i < k; ++i)
        q.push(root->GetNextNearest(city));

    return q;
}  // Had ; here

int SpatialTree::Count() const {
    return size;
}

int SpatialTree::Depth() const {
    return root->Depth();
}


// Simple tree display, left justified
void SpatialTree::Print() const {
    if (!root)
        cout << "The tree is empty!" << endl;
    else
        root->Print();
}
