#include <iostream>
#include "directory.h"
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

int main(int argc, char* argv[]) {
    Directory* curDir = new Directory(nullptr);

    for (string line : getlines(argc, argv)) {
        if (line.substr(0, 4) == "$ cd") cd(curDir, line.substr(5));
        else if (line.front() != '$') curDir->add(line);
    }

    cd(curDir, "/");
    const int neededSpace = 30000000 - (70000000 - curDir->getSize());

    cout << "Part 1: " << curDir->getAnswer_pt1() << endl;
    cout << "Part 2: " << curDir->getAnswer_pt2(neededSpace) << endl;

    return 0;
}
