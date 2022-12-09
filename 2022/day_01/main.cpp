#include <algorithm>
#include <iostream>
#include "jmch/getlines.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<int> elvesCals;
    int maxElfCals = 0, curElfCals = 0, sum = 0;
    
    for (string line : getlines(argc, argv)) {
        try {
            curElfCals += stoi(line);
        } catch (invalid_argument &e) { // Thrown when empty line is reached.
            maxElfCals = (maxElfCals < curElfCals) ? curElfCals : maxElfCals;
            
            elvesCals.push_back(curElfCals);
            curElfCals = 0;
        }
    }

    sort(elvesCals.begin(), elvesCals.end());
    for (int i = 0; i < 3; i++) {
        sum += elvesCals.back(); elvesCals.pop_back();
    }

    cout << "Part 1: " << maxElfCals << endl;
    cout << "Part 2: " << sum << endl;

    return 0;
}
