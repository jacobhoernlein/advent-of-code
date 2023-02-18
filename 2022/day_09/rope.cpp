#include "rope.h"

using namespace std;

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

Rope::Rope(int length) {
    knots = vector<pair<int, int>>(length, pair<int, int>(0, 0));
}

void Rope::move(char direction, int count) {
    // If direction is L or R, modify first element of head. Else second.
    // If direction is R or U, increase that element. Else decrease.
    int &headElement = (direction == 'L' || direction == 'R') ?
        knots.front().first : knots.front().second;
    const int change = (direction == 'R' || direction == 'U') ?
        1 : -1;
    
    for (int i = 0; i < count; i++) {
        headElement += change;
        
        // Move each of the following knots.
        vector<pair<int, int>>::iterator it;
        for (it = knots.begin(); it < knots.end() - 1; it++) {
            moveKnot(*it, *(it + 1));
        }

        // Add the position of the last knot.
        visitedPoints.insert(knots.back());
    }
}

int Rope::countVisitedPoints() const {
    return visitedPoints.size();
}
