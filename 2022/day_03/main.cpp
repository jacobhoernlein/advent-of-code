#include <iostream>
#include <unordered_set>
#include "jmch/getlines.h"

using namespace std;

// Number of elves per group.
const int NUM_ELVES = 3;

int getVal_pt1(const string &line) {
    unordered_set<char> compartment1;
    int i;

    // Adds characters of first compartment to set.
    for (i = 0; i < line.length() / 2; i++) {
        compartment1.insert(line[i]);
    }
    // Returns value of first character in second compartment
    // That is also in the first compartment.
    for (; i < line.length(); i++) {
        if (compartment1.find(line[i]) != compartment1.end()) {
            char c = line[i];

            if (c >= 'a' && c <= 'z') {
                return c - 'a' + 1;
            }
            else {
                return c - 'A' + 27;
            }
        }
    }
    return 0;
}

int getVal_pt2(const vector<string> &elves) {
    vector<unordered_set<char>> shared(elves.size() - 1);
    
    // Adds unique chars to first set in vector.
    for (char c : elves.at(0)) {
        if (shared.at(0).find(c) == shared.at(0).end()) {
            shared.at(0).insert(c);
        }
    }
    // Adds shared characters between current string and
    // previous string to current set in vector. 
    for (int i = 1; i < shared.size(); i++) {
        for (char c : elves.at(i)) {
            if (shared.at(i - 1).find(c) != shared.at(i - 1).end()) {
                shared.at(i).insert(c);
            }
        }
    }
    // For the last string, returns value of first character shared.
    for (char c : elves.back()) {
        if (shared.back().find(c) != shared.back().end()) {
            if (c >= 'a' && c <= 'z') {
                return c - 'a' + 1;
            }
            else {
                return c - 'A' + 27;
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int sum_pt1 = 0, sum_pt2 = 0, i = 0;
    vector<string> elves(NUM_ELVES);

    for (string line : getlines(argc, argv)) {
        sum_pt1 += getVal_pt1(line);
        elves.at(i++ % NUM_ELVES) = line;
        if (i % NUM_ELVES == 0) {
            sum_pt2 += getVal_pt2(elves);
        }
    }

    cout << "Part 1: " << sum_pt1 << endl;
    cout << "Part 2: " << sum_pt2 << endl;

    return 0;
}
