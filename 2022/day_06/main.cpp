#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

template<class T, class IT>
int findNonRepeating(const IT begin, const IT end, const int s) {
    unordered_set<T> set;
    bool allUnique;

    for (int p = 0; true; p++) {
        set.clear();
        allUnique = true;
        
        // Loop s times from the given p value,
        // Trying to find unique sub-iterable.
        for (int i = 0; i < s; i++) {
            if (begin + p + i >= end) {
                // End reached without finding match.
                // Return to avoid seg-fault.
                return -1;
            }
            if (set.find(*(begin + p + i)) != set.end()) {
                // Value already in set.
                allUnique = false;
                break;
            } else {
                // Value not in set. Insert.
                set.insert(*(begin + p + i));
            }
        }
        if (allUnique) {
            // Unique sub-iterable found. Return last index.
            return p + s - 1;
        }
    }
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

    cout << "Part 1: " << findNonRepeating<char>(input.begin(), input.end(), 4) + 1 << endl;
    cout << "Part 1: " << findNonRepeating<char>(input.begin(), input.end(), 14) + 1 << endl;

    return 0;
}
