#include <iostream>
#include <sstream>
#include "getlines.h"
#include "rope.h"

using namespace std;

int main(int argc, char* argv[]) {
    Rope rope1(1), rope2(9);
    stringstream ss;
    char direction; int count;

    for (string line : getlines(argc, argv)) {
        ss.str(line);
        ss >> direction >> count;
        rope1.moveHead(direction, count);
        rope2.moveHead(direction, count);
        ss.clear();
    }

    cout << "Part 1: " << rope1.getVisitedPoints() << endl;
    cout << "Part 2: " << rope2.getVisitedPoints() << endl;

    return 0;
}
