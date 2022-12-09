#include <iostream>
#include <sstream>
#include "rope.h"
#include "jmch/getlines.h"

using namespace std;

int main(int argc, char* argv[]) {
    Rope rope1(2), rope2(10);
    
    stringstream ss;
    char direction; int count;

    for (string line : getlines(argc, argv)) {
        ss.clear(); ss.str(line);
        ss >> direction >> count;

        rope1.move(direction, count);
        rope2.move(direction, count);
    }

    cout << "Part 1: " << rope1.countVisitedPoints() << endl;
    cout << "Part 2: " << rope2.countVisitedPoints() << endl;

    return 0;
}
