#include <iostream>
#include <sstream>
#include "getlines.h"

using namespace std;

void moveBoxes_pt1(vector<vector<char>> &stacks, const string &line) {
    stringstream ss(line);
    string dummy;
    int numBoxes, source, destination;
    char box;
    ss >> dummy >> numBoxes >> dummy >> source >> dummy >> destination;
    source--; destination--;

    for (int i = 0; i < numBoxes; i++) {
        box = stacks.at(source).back(); stacks.at(source).pop_back();
        stacks.at(destination).push_back(box);
    }
}

void moveBoxes_pt2(vector<vector<char>> &stacks, const string &line) {
    stringstream ss(line);
    string dummy;
    int numBoxes, source, destination;
    char box;
    ss >> dummy >> numBoxes >> dummy >> source >> dummy >> destination;
    source--; destination--;

    vector<char> subStack;

    for (int i = 0; i < numBoxes; i++) {
        box = stacks.at(source).back(); stacks.at(source).pop_back();
        subStack.push_back(box);
    }
    for (int i = 0; i < numBoxes; i++) {
        box = subStack.back(); subStack.pop_back();
        stacks.at(destination).push_back(box);
    }
}

int main(int argc, char* argv[]) {
    vector<vector<char>> stacks1 = {
        {'W', 'R', 'F'},
        {'T', 'H', 'M', 'C', 'D', 'V', 'W', 'P'},
        {'P', 'M', 'Z', 'N', 'L'},
        {'J', 'C', 'H', 'R'},
        {'C', 'P', 'G', 'H', 'Q', 'T', 'B'},
        {'G', 'C', 'W', 'L', 'F', 'Z'},
        {'W', 'V', 'L', 'Q', 'Z', 'J', 'G', 'C'},
        {'P', 'N', 'R', 'F', 'W', 'T', 'V', 'C'},
        {'J', 'W', 'H', 'G', 'R', 'S', 'V'}
    };
    vector<vector<char>> stacks2 = {
        {'W', 'R', 'F'},
        {'T', 'H', 'M', 'C', 'D', 'V', 'W', 'P'},
        {'P', 'M', 'Z', 'N', 'L'},
        {'J', 'C', 'H', 'R'},
        {'C', 'P', 'G', 'H', 'Q', 'T', 'B'},
        {'G', 'C', 'W', 'L', 'F', 'Z'},
        {'W', 'V', 'L', 'Q', 'Z', 'J', 'G', 'C'},
        {'P', 'N', 'R', 'F', 'W', 'T', 'V', 'C'},
        {'J', 'W', 'H', 'G', 'R', 'S', 'V'}
    };

    for (string line : getlines(argc, argv)) {
        moveBoxes_pt1(stacks1, line);
        moveBoxes_pt2(stacks2, line);
    }

    cout << "Part 1: ";
    for (int i = 0; i < 9; i++) {
        cout << stacks1.at(i).back();
    }
    cout << endl;

    cout << "Part 2: ";
    for (int i = 0; i < 9; i++) {
        cout << stacks2.at(i).back();
    }
    cout << endl;

    return 0;
}
