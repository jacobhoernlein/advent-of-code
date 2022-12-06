#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

int findRepeating(const string &input, const int s) {
    unordered_set<char> chars;
    bool allUnique;

    for (int p = 0; p <= input.size() - s; p++) {
        chars = {};
        allUnique = true;
        
        for (int i = 0; i < s; i++) {
            if (chars.find(input[p + i]) != chars.end()) {
                allUnique = false;
                break;
            }
            else chars.insert(input[p + i]);
        }
        if (allUnique) {
            return p + s;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout<< "Supply input file." << endl;
        return 1;
    }
    
    ifstream file;
    string input;

    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Invalid input file." << endl;
        return 2;
    }
    file >> input;
    file.close();

    cout << "Part 1: " << findRepeating(input, 4) << endl;
    cout << "Part 2: " << findRepeating(input, 14) << endl;

    return 0;
}
