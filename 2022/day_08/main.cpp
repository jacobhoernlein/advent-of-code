#include <iostream>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

bool isVisible(const vector<vector<int>> &trees, const int i, const int j) {
    int k, height = trees.at(i).at(j);
    
    // Check going north
    bool visible = true;
    for (k = i - 1; k >= 0; k--) {
        if (trees.at(k).at(j) >= height) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    // Check going east
    visible = true;
    for (k = j + 1; k < trees.at(i).size(); k++) {
        if (trees.at(i).at(k) >= height) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    // Check going south
    visible = true;
    for (k = i + 1; k < trees.size(); k++) {
        if (trees.at(k).at(j) >= height) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    // Check going west
    visible = true;
    for (k = j - 1; k >= 0; k--) {
        if (trees.at(i).at(k) >= height) {
            visible = false;
            break;
        }
    }
    return visible;
}

int getScenicScore(const vector<vector<int>> &trees, const int i, const int j) {
    int k, height = trees.at(i).at(j);
    int north = 0, east = 0, south = 0, west = 0;
    
    for (k = i - 1; k >= 0; k--) {
        north++;
        if (trees.at(k).at(j) >= height) break;
    }
    for (k = j + 1; k < trees.at(i).size(); k++) {
        east++;
        if (trees.at(i).at(k) >= height) break;
    }
    for (k = i + 1; k < trees.size(); k++) {
        south++;
        if (trees.at(k).at(j) >= height) break;
    }
    for (k = j - 1; k >= 0; k--) {
        west++;
        if (trees.at(i).at(k) >= height) break;
    }

    return north * east * south * west;
}

int part1(const vector<vector<int>> &trees) {
    int i, j, total = 0;
    for (i = 0; i < trees.size(); i++)
        for (j = 0; j < trees.at(i).size(); j++)
            if (isVisible(trees, i, j)) total++;
    return total;
}

int part2(const vector<vector<int>> &trees) {
    int i, j, score, greatest = 0;
    for (i = 0; i < trees.size(); i++) {
        for (j = 0; j < trees.at(i).size(); j++) {
            score = getScenicScore(trees, i, j);
            if (score > greatest) greatest = score;
        }
    }
    return greatest;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> trees;
    for (string line : getlines(argc, argv)) {
        trees.push_back({});
        for (char c : line) {
            trees.back().push_back(c - '0');
        }
    }

    cout << "Part 1: " << part1(trees) << endl;
    cout << "Part 2: " << part2(trees) << endl;

    return 0;
}
