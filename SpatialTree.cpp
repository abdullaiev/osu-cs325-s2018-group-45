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
SpatialTree::SpatialTree(vector<City*> cities) {
	size = cities.size();
	vector<City*> data;
	
	
	
	if (size < 1) {
		root == NULL;
		return;
	}
	
	vector<City*> citiesCopy = cities;
	sort(cities.begin(), cities.end(), City::CompareX);
	int iMid = size / 2;
	root = new SpatialNode(cities[iMid]);
	
	int iLow = 0;
	int iHigh = size;
	
	
		
};

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
};

City* SpatialTree::GetNextNearest(City* city) {
	return NULL;
};

queue<City*> SpatialTree::GetKNearest(City* city, int k) {
	return queue<City*>();
};

int SpatialTree::Count() const{
	return size;
}


// Simple tree display, left justified
void SpatialTree::Print() const{
	if (!root)
		return;
	root->Print();
}