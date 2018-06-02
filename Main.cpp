#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h"
#include "City.h"

using std::endl;
using std::cout;
using std::vector;
using std::sort;

int main(int argc, char* argv[]) {
	vector<City*> cities;
	
	cities.push_back(new City(5, 5, 1));
	cities.push_back(new City(4, 3, 3));
	cities.push_back(new City(3, 1, 2));
	cities.push_back(new City(2, 2, 5));
	cities.push_back(new City(1, 4, 4));
	
	sort(cities.begin(), cities.end(), City::Compare);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
	City::CompareByX();
	sort(cities.begin(), cities.end(), City::Compare);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
	City::CompareByY();
		sort(cities.begin(), cities.end(), City::Compare);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	return 0;
}
