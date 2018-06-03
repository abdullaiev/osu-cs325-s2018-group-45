#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

#include "Node.h"
#include "City.h"
#include "Tour.h"
#include "SpatialTree.h"
#include "Problem.h"

using std::endl;
using std::cout;
using std::vector;
using std::sort;
using std::string;
using std::queue;

int main(int argc, char* argv[]) {
	vector<City*> cities;
	
	cities.push_back(new City(5, 5, 1));
	cities.push_back(new City(4, 3, 3));
	cities.push_back(new City(3, 1, 2));
	cities.push_back(new City(2, 2, 6));
	cities.push_back(new City(1, 4, 4));
	cities.push_back(new City(0, 6, 1));
	cities.push_back(new City(6, -6, 7));
	
	sort(cities.begin(), cities.end(), City::CompareX);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
		sort(cities.begin(), cities.end(), City::CompareY);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
	sort(cities.begin(), cities.end(), City::CompareID);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
	SpatialNode* root = new SpatialNode(cities[0]);
	root->left = new SpatialNode(cities[1]);
	root->right = new SpatialNode(cities[2]);
	root->left->left = new SpatialNode(cities[3]);
	root->left->right = new SpatialNode(cities[4]);
	root->right->right = new SpatialNode(cities[5]);
	
	root->Print();
	
	delete root;
	
	Tour t = Tour(cities);
	
	for (int i = 0; i < t.Count(); ++i) {
		City* city = t.GetCity(i);
		cout << city->prev->ToString() << " <- " << city->ToString() << " -> " << city->next->ToString() << endl;
	}
	cout << endl << "Nearest to city 0" << endl;
	queue<City*> neighbors = t.GetNearest(0,4);
	cout << "Got " << neighbors.size() << " neighbors." << endl;
	while (!neighbors.empty()) {
		cout << neighbors.front()->ToString() << endl;
		neighbors.pop();
	}
	
	cout << endl << "Building spatial tree..." << endl << endl;
	
	vector<City> cityObjs = Problem("./samples/tsp_example_3.txt").getData();
	vector<City*> cityPtrs(cityObjs.size());
	for (int i = 0; i < cityPtrs.size(); ++i)
		cityPtrs[i] = &cityObjs[i];
	
	SpatialTree tree(cityPtrs);
	
	cout << "Tree depth: " << tree.Depth() << endl;
	
	cout << "Getting cities near 1000,1000" << endl;
	City testCity(0, 1000, 1000);
	queue<City*> results = tree.GetKNearest(&testCity, 200);
	
	while (!results.empty()) {
		cout << results.front()->ToString() << "Distance: " << results.front()->DistanceTo(&testCity) << endl;
		results.pop();
	}
	
	
	
	return 0;
}
