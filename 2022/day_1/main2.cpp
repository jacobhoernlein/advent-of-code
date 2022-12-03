#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Supply input file." << endl;
        return 1;
    }
    
    vector<int> elvesCals;
    int maxElfCals = 0, curElfCals = 0, sum = 0;

    ifstream file;
    string line;
    
    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Invalid input file." << endl;
        return 2;
    }
    while (getline(file, line)) {
        try {
            curElfCals += stoi(line);
        } catch (invalid_argument) { // Thrown when empty line is reached.
            maxElfCals = (maxElfCals < curElfCals) ? curElfCals : maxElfCals;
            
            elvesCals.push_back(curElfCals);
            curElfCals = 0;
        }
    }
    file.close();

    // Part 1 operates in O(N) time, where N is the number of lines in the file.
    cout << "Part 1: " << maxElfCals << endl;

    // Part 2 operates in O(NlogN) time, since std::sort is NlogN complexity.
    sort(elvesCals.begin(), elvesCals.end());
    for (int i = 0; i < 3; i++) {
        sum += elvesCals.back(); elvesCals.pop_back();
    }
    cout << "Part 2: " << sum << endl;

    return 0;
}
