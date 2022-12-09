#include "rope.h"

using namespace std;

Rope::Rope(int length) {
    knots = vector(length, pair(0, 0));
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

void Rope::move(char direction, int count) {
    for (int i = 0; i < count; i++) {
        // Move the head to the proper direction.
        if (direction == 'R') knots.front().first++;
        if (direction == 'L') knots.front().first--;
        if (direction == 'U') knots.front().second++;
        if (direction == 'D') knots.front().second--;
        
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
