#include <iostream>
#include "Node.h"
#include "City.h"

using std::endl;
using std::cout;

int main(int argc, char* argv[]) {
	City test(1, 100, -200);
	cout << endl << test.ToString() << endl;
	return 0;
}
