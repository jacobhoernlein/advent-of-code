#include <sstream>
#include "rope.h"

using namespace std;

Rope::Rope(int length) {
    head.first = 0;
    head.second = 0;
    
    if (length < 1) length = 1;
    tail = vector(length, pair(0, 0));
}

// Moves the slave based on how far away the master is.
void moveKnot(pair<int, int> &master, pair<int, int> &slave) {
    int dx = master.first - slave.first;
    int dy = master.second - slave.second;

    if (dx > 1 || dx < -1) {
        slave.first += (dx > 0) ? 1 : -1;
        if (dy) slave.second += (dy > 0) ? 1 : -1;
    }
    else if (dy > 1 || dy < -1) {
        slave.second += (dy > 0) ? 1 : -1;
        if (dx) slave.first += (dx > 0) ? 1 : -1;
    }
}

void Rope::moveHead(char direction, int count) {
    for (int i = 0; i < count; i++) {
        // Move the head to the proper direction.
        if (direction == 'R') head.first++;
        if (direction == 'L') head.first--;
        if (direction == 'U') head.second++;
        if (direction == 'D') head.second--;
        
        // Move the first knot of the tail.
        moveKnot(head, tail.front());
        
        // Move the rest of the knots.
        vector<pair<int, int>>::iterator it;
        for (it = tail.begin() + 1; it < tail.end(); it++) {
            moveKnot(*(it - 1), *it);
        }

        // Add the current point the tail is at to the set.
        stringstream ss;
        ss << tail.back().first << " " << tail.back().second;
        visitedPoints.insert(ss.str());
        ss.clear();
    }
}

int Rope::getVisitedPoints() {
    return visitedPoints.size();
}
