#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Node.h"
#include "City.h"
#include "Problem.h"


using std::endl;
using std::cout;
using std::vector;
using std::sort;

int main(int argc, char* argv[]) {
/**
	vector<City*> cities;
	
	cities.push_back(new City(5, 5, 1));
	cities.push_back(new City(4, 3, 3));
	cities.push_back(new City(3, 1, 2));
	cities.push_back(new City(2, 2, 5));
	cities.push_back(new City(1, 4, 4));
	
	sort(cities.begin(), cities.end(), City::CompareID);
	for (int i = 0; i < cities.size(); ++i) {
		cout << cities[i]->ToString() << endl;
	}
	cout << endl;
	
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

**/
  std::string filename;

  if(argc ==1)
  {
    std::cout << "Pleaes Enter the filename: ";
    std::cin >> filename;
  }

  else
  {
    filename = argv[1];

  }


	return 0;
}
