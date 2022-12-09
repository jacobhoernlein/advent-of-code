#ifndef ROPE_H_
#define ROPE_H_

#include <unordered_set>
#include <vector>
#include "jmch/hashpair.h"

class Rope {
    std::vector<std::pair<int, int>> knots;
    std::unordered_set<std::pair<int, int>, hash_pair> visitedPoints;
public:
    Rope(int length);    
    void move(char direction, int count);
    int countVisitedPoints() const;
};

#endif
