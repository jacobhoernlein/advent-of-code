#include <iostream>
#include <sstream>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

void drawLines(vector<string> &map, const string &line) {
    int x, y, prevX, prevY; char d;
    
    stringstream ss(line);
    ss >> prevX >> d >> prevY >> d >> d; // Read first point

    while (true) {
        ss >> x >> d >> y;

        if (prevX == x) {
            // Draw on y axis
            if (prevY < y) for (int i = prevY; i <= y; i++) map.at(i).at(x) = '#'; 
            else for (int i = y; i <= prevY; i++) map.at(i).at(x) = '#';

        } else {
            // Draw on x axis
            if (prevX < x) for (int i = prevX; i <= x; i++) map.at(y).at(i) = '#';
            else for (int i = x; i <= prevX; i++) map.at(y).at(i) = '#';
        }

        if (!ss.eof()) {
            ss >> d >> d; // Read arrows.
            prevX = x; prevY = y;
        } else break;
    }
}

int part1(vector<string> &map) {
    int count = 0;
    int curX, curY;
    
    while (true) { // Keep spawning sand until one falls off map
        curX = 500; curY = 0;
        while (true) { // Keep falling until immobilized
            if (curY > 161) return count; // Fallen off map

            if (map.at(curY + 1).at(curX) == '.') {
                curY++;
            }
            else if (map.at(curY + 1).at(curX - 1) == '.') {
                curX--; curY++;
            }
            else if (map.at(curY + 1).at(curX + 1) == '.') {
                curX++; curY++;
            }
            else {
                // Can't move
                map.at(curY).at(curX) = 'o';
                count++;
                break;
            }
        }
    }
}

int part2(vector<string> &map) {
    int count = 0;
    int curX, curY;
    
    while (true) { // Keep spawning sand until one comes to rest at top.
        curX = 500; curY = 0;
        while (true) { // Keep falling until immobilized
            if (map.at(curY + 1).at(curX) == '.') {
                curY++;
            }
            else if (map.at(curY + 1).at(curX - 1) == '.') {
                curX--; curY++;
            }
            else if (map.at(curY + 1).at(curX + 1) == '.') {
                curX++; curY++;
            }
            else {
                // Can't move
                map.at(curY).at(curX) = 'o';
                count++;
                if (curY == 0) return count; // Immobilized at top.
                break;
            }
        }
    }
}

void clearMap(vector<string> &map) {
    for (string &row : map) {
        for (char &c : row) {
            if (c == 'o') c = '.';
        }
    }
}

int main(int argc, char* argv[]) {
    vector<string> map(164, string(1000, '.'));
    map.at(163) = string(1000, '#'); // Add "bedrock"

    for (string line : getlines(argc, argv)) {
        drawLines(map, line);
    }

    cout << "Part 1: " << part1(map) << endl; clearMap(map);
    cout << "Part 2: " << part2(map) << endl;

    return 0;
}
