#include <iostream>
#include <unordered_map>
#include "getlines.h"

using namespace std;

class Directory {
    int filesSize;
    Directory* parent;
    unordered_map<string, Directory*> children;
public:
    Directory(Directory* parent);
    void add(string line);
    int getSize();

    int getAnswer_pt1();
    int getAnswer_pt2(const int unusedSpace);

    friend void cd(Directory* &curDir, string name); 
};

// Initializes a new directory with a pointer to the parent.
Directory::Directory(Directory* parent) {
    this->filesSize = 0;
    this->parent = parent;
}

// Returns the size of the files of the current directory
// and recursively gets size of subdirectories.
int Directory::getSize() {
    int size = this->filesSize;

    unordered_map<string, Directory*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        size += it->second->getSize();
    }

    return size;
}

// Either adds a new subdirectory or increases filesSize of current directory.
void Directory::add(string line) {
    if (line.substr(0, 3) == "dir") children[line.substr(4)] = new Directory(this);
    else filesSize += stoi(line);
}

// Gets the sum of all the directory sizes < 10000.
int Directory::getAnswer_pt1() {
    int answer = 0;

    if (getSize() <= 100000) answer += getSize();
    
    unordered_map<string, Directory*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        answer += it->second->getAnswer_pt1();
    }
    
    return answer;
}

// Finds the smallest directory with size greater than neededSpace.
int Directory::getAnswer_pt2(const int neededSpace) {
    int lowest = getSize();
    if (lowest < neededSpace) return lowest;
    
    unordered_map<string, Directory*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        int size = it->second->getAnswer_pt2(neededSpace);
        if (size >= neededSpace && size < lowest) lowest = size;
    }
    
    return lowest;
}

// Change the pointer curDir based on dirName
void cd(Directory* &curDir, string dirName) {
    if (dirName == "/") while (curDir->parent != nullptr) curDir = curDir->parent;
    else if (dirName == "..") curDir = curDir->parent;
    else curDir = curDir->children[dirName];
}

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
