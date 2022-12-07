#include <fstream>
#include <vector>
#include "getlines.h"

using namespace std;

vector<string> getlines(int argc, char** argv) {
    if (argc != 2) throw invalid_argument("Supply input file.");
            
    ifstream file(argv[1]);
    if (!file.is_open()) throw fstream::failure("Invalid input file.");

    vector<string> lines;
    string line;

    while (getline(file, line)) lines.push_back(line);
    file.close();

    return lines;
}
