#ifndef ROPE_H_
#define ROPE_H_

#include <unordered_set>
#include <vector>
#include "jmch/hashpair.h"

class Rope {
    std::vector<std::pair<int, int>> knots;
    std::unordered_set<std::pair<int, int>, hash_pair> visitedPoints;
public:
    // Constructs a new Rope with the given length.
    Rope(int length);    

    // Moves the head of the Rope in the given direction, count times.
    void move(char direction, int count);
    
    // Return the number of points visited by the last knot in the rope.
    int countVisitedPoints() const;
};

#endif
