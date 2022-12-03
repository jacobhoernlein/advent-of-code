#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Supply input file." << endl;
        return 1;
    }
    
    priority_queue<int> calHeap;
    int elf1, elf2, elf3, curCals = 0;

    ifstream file;
    string line;
    
    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Invalid input file." << endl;
        return 2;
    }
    while (getline(file, line)) {
        try {
            curCals += stoi(line);
        } catch (invalid_argument) { // Thrown when empty line is reached.
            calHeap.push(curCals);
            curCals = 0;
        }
    }
    file.close();

    elf1 = calHeap.top(); calHeap.pop();
    elf2 = calHeap.top(); calHeap.pop();
    elf3 = calHeap.top();

    cout << "Part 1: " << elf1 << endl;
    cout << "Part 2: " << elf1 + elf2 + elf3 << endl;

    return 0;
}
