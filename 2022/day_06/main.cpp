#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

template<typename T>
int findNonRepeating(T *begin, T *end, int s) {
    unordered_set<T> set;
    bool allUnique;

    for (int p = 0; true; p++) {
        set.clear();
        allUnique = true;

        for (int i = 0; i < s; i++) {
            if (begin + p + i >= end) return -1;

            if (set.find(*(begin + p + i)) != set.end()) {
                allUnique = false;
                break;
            } else set.insert(*(begin + p + i));
        }

        if (allUnique) return p + s - 1;
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

    cout << "Part 1: " << findNonRepeating(&input.front(), &input.back(), 4) + 1 << "\n";
    cout << "Part 2: " << findNonRepeating(&input.front(), &input.back(), 14) + 1 << endl;

    return 0;
}
