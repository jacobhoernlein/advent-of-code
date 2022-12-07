#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include <string>
#include <unordered_map>

// Represents a directory within a file system.
class Directory {
    int filesSize;
    Directory* parent;
    std::unordered_map<std::string, Directory*> children;
public:
    // Initializes a new directory with a pointer to the parent.
    Directory(Directory* parent);
    
    // Either adds a new subdirectory or increases filesSize of current directory.
    void add(const std::string &line);
    
    // Returns the size of the files of the current directory
    // and recursively gets size of subdirectories.
    int getSize();

    // Gets the sum of all the directory sizes < 10000.
    int getAnswer_pt1();
    
    // Finds the smallest directory with size greater than neededSpace.
    int getAnswer_pt2(const int unusedSpace);

    // Change the pointer curDir based on dirName
    friend void cd(Directory* &curDir, const std::string &name); 
};

#endif
