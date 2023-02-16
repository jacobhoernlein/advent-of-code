#include <iostream>
#include <sstream>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

int getScore_pt1(char elf, char me) {
    switch (me) {
        case 'X': // Rock
            switch (elf) {
                case 'A': // Draw
                    return 4;
                case 'B': // Lose
                    return 1;
                case 'C': // Win
                    return 7;
            }
        case 'Y': // Paper
            switch (elf) {
                case 'A': // Win
                    return 8;
                case 'B': // Draw
                    return 5;
                case 'C': // Lose
                    return 2;
            }
        case 'Z': // Scissors
            switch (elf) {
                case 'A': // Lose
                    return 3;
                case 'B': // Win
                    return 9;
                case 'C': // Draw
                    return 6;
            }
    }
    throw invalid_argument("Elf must be A, B, C. Me must be X, Y, Z.");
}

int getScore_pt2(char elf, char me) {
    switch (me) {
        case 'X': // Lose
            switch (elf) {
                case 'A': // Scissors
                    return 3;
                case 'B': // Rock
                    return 1;
                case 'C': // Paper
                    return 2;
            }
        case 'Y': // Draw
            switch (elf) {
                case 'A': // Rock
                    return 4;
                case 'B': // Paper
                    return 5;
                case 'C': // Scissors
                    return 6;
            }
        case 'Z': // Win
            switch (elf) {
                case 'A': // Paper
                    return 8;
                case 'B': // Scissors
                    return 9;
                case 'C': // Rock
                    return 7;
            }
    }
    throw invalid_argument("Elf must be A, B, C. Me must be X, Y, Z.");
}

int main(int argc, char* argv[]) {
    int score_pt1 = 0, score_pt2 = 0;
    char elf, me;
    stringstream ss;
    
    for (string line : getlines(argc, argv)) {
        ss.str(line);
        ss >> elf >> me;

        score_pt1 += getScore_pt1(elf, me);
        score_pt2 += getScore_pt2(elf, me);
    }

    cout << "Part 1: " << score_pt1 << endl;
    cout << "Part 2: " << score_pt2 << endl;

    return 0;
}
