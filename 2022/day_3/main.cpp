#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

using namespace std;

int getVal_pt1(const string &line) {
    unordered_set<char> compartment1;
    int i;

    for (i = 0; i < line.length() / 2; i++) {
        compartment1.insert(line[i]);
    }
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
    unordered_set<char> elf1, elf2;

    for (char c : elves.at(0)) {
        elf1.insert(c);
    }
    for (char c : elves.at(1)) {
        if (elf1.find(c) != elf1.end() && elf2.find(c) == elf2.end()) {
            elf2.insert(c);
        }
    }
    for (char c : elves.at(2)) {
        if (elf2.find(c) != elf2.end()) {
            if (c >= 'a' && c <= 'z') {
                return c - 'a' + 1;
            }
            else {
                return c - 'A' + 27;
            }
        }
    }

    return ' ';
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Supply input file." << endl;
        return 1;
    }
    
    int sum_pt1 = 0, sum_pt2 = 0, i = 0;
    vector<string> elves(3);

    ifstream file;
    string line;

    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Invalid input file." << endl;
        return 2;
    }
    while (getline(file, line)) {        
        sum_pt1 += getVal_pt1(line);
        elves.at(i++) = line;
        if (i == 3) {
            sum_pt2 += getVal_pt2(elves);
            i = 0;
        }
    }
    file.close();

    cout << "Part 1: " << sum_pt1 << endl;
    cout << "Part 2: " << sum_pt2 << endl;

    return 0;
}
