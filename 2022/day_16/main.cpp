#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Supply input file." << endl;
        return 1;
    }
    
    ifstream file;
    string line;

    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Invalid input file." << endl;
        return 2;
    }
    while (getline(file, line)) {        
        
    }
    file.close();

    cout << "Part 1: " << 0 << endl;
    cout << "Part 2: " << 0 << endl;

    return 0;
}
