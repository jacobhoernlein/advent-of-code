#include "directory.h"

using namespace std;

Directory::Directory(Directory* parent) {
    this->filesSize = 0;
    this->parent = parent;
}

void Directory::add(const string &line) {
    if (line.substr(0, 3) == "dir") children[line.substr(4)] = new Directory(this);
    else filesSize += stoi(line);
}

int Directory::getSize() {
    int size = this->filesSize;

    unordered_map<string, Directory*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        size += it->second->getSize();
    }

    return size;
}

int Directory::getAnswer_pt1() {
    int answer = 0;

    if (getSize() <= 100000) answer += getSize();
    
    unordered_map<string, Directory*>::iterator it;
    for (it = children.begin(); it != children.end(); it++) {
        answer += it->second->getAnswer_pt1();
    }
    
    return answer;
}

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

void cd(Directory* &curDir, const string &name) {
    if (name == "/") while (curDir->parent != nullptr) curDir = curDir->parent;
    else if (name == "..") curDir = curDir->parent;
    else curDir = curDir->children[name];
}
