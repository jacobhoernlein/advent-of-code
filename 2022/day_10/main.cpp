#include <iostream>
#include "cpu.h"
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

int main(int argc, char* argv[]) {
    CPU cpu;
    
    for (string line : getlines(argc, argv)) {
        if (line.substr(0, 4) == "noop") cpu.doCycle();
        else cpu.addx(stoi(line.substr(5)));
    }

    cout << "Part 1: " << cpu.sumStrengths() << '\n';
    cout << "Part 2:\n";
    cpu.printScreen();

    return 0;
}
