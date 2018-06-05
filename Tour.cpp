/****************************************
 * Group 45
 * CS 325 - Spring 2018
 * 
 * Implementation for the CTour class
 ****************************************/
#include <queue>
#include <iostream>
#include "Tour.h"
#include "City.h"


using std::queue;
using std::cout;
using std::endl;


Tour::Tour(vector < City * > cities) {
    size = cities.size();
    this->cities = cities;

    for (int i = 0; i < size; ++i) {
        if (i > 0) {
            this->cities[i]->prev = this->cities[i - 1];
            this->cities[i - 1]->next = this->cities[i];
        }
    }
    if (size > 1) {
        this->cities[0]->prev = this->cities[size - 1];
        this->cities[size - 1]->next = this->cities[0];
    }
}

City *Tour::GetCity(int index) const {
    return cities[index];
}

queue<City *> Tour::GetNearest(int index, int count) const {
    queue < City * > q;

    // Catch invalid index
    if (index < 0 || index > size - 1)
        return q;

    // Don't return more than there are
    if (count > size)
        count = size;
    if (size < 1)
        return q;

    // TEMPORARY - Just get next in order
    City *left = cities[index];
    City *right = left;

    // Alternate left and right nearest along path
    for (int i = 0; i < count; ++i) {
        if (i % 2 == 0) {
            q.push(left->prev);
            left = left->prev;
        } else {
            q.push(right->next);
            right = right->next;
        }
    }
    return q;
}

bool Tour::IsVisited(int index) const {
    return cities[index]->visited;
}

int Tour::Count() const {
    return size;
}
