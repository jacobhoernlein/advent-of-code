#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <set>
#include <vector>

#include "jmch/getlines.h"

using namespace std;

int getNumWon(const string& line) {
    stringstream ss(line);
    string temp;
    ss >> temp >> temp; // Get rid of card number.

    // Using vectors is faster than sets for small sizes.
    vector<int> winningNums, myNums;

    while (true) {
        ss >> temp;
        if (temp == "|") 
            break;
        winningNums.push_back(stoi(temp));
    }

    while (ss >> temp) 
        myNums.push_back(stoi(temp));
    
    int numWon = 0;
    for (int n : myNums)
        if (find(winningNums.begin(), winningNums.end(), n) != winningNums.end())
            numWon++;

    return numWon;
}

int main(int argc, char** argv) {
    auto lines = jmch::getlines(argc, argv);

    int part1 = 0;
    vector<int> part2(lines.length(), 1);

    for (int i = 0; i < lines.length(); i++) {
        int matching = getNumWon(lines[i]);
        part1 += 1 << (matching - 1);

        for (int j = 0; j < matching; j++) 
            part2[i + j + 1] += part2[i];
    }

    cout << "Part One: " << part1 << endl;
    cout << "Part Two: " << accumulate(part2.begin(), part2.end(), 0) << endl;

    return 0;
}
