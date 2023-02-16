#include <algorithm>
#include <iostream>
#include <sstream>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

struct Interval {
    int min;
    int max;
    Interval(int min, int max) {
        this->min = min;
        this->max = max;
    }
    friend bool operator<(const Interval &i1, const Interval &i2) {
        return i1.min < i2.min;
    }
};

struct Sensor {
    int x;
    int y;
    int d;
    Sensor(int x, int y, int d) {
        this->x = x;
        this->y = y;
        this->d = d;
    }
};

int countPoints(char mode, int num, const vector<Sensor> &sensors, const bool reduce = true) {
    vector<Interval> intervals;
    vector<Interval> merged;
    int min, max;

    for (const Sensor &s : sensors) {
        // Reading y coordinate, find range of xs.
        if (mode == 'y') {
            min = s.x - s.d + abs(s.y - num);
            max = s.x + s.d - abs(s.y - num);
        // Reading x coordinate, find range of ys.
        } else if (mode == 'x') {
            min = s.y - s.d + abs(s.x - num);
            max = s.y + s.d - abs(s.x - num);
        // Bad input.
        } else return 0;
        
        // Sensor does not scan given row/col.
        if (min > max) continue;
        
        // If true, shortens the ranges to be within 0-4000000.
        if (reduce) {
            if (min < 0) min = 0;
            if (max > 4000000) max = 4000000;
        }

        intervals.push_back(Interval(min, max));
    }
    sort(intervals.begin(), intervals.end());
    
    // Merge the intervals
    vector<Interval>::iterator it = intervals.begin();
    Interval prev = *it, cur = *it; it++;
    while (it != intervals.end()) {
        cur = *it;
        // If there is overlap, merge the two intervals.
        if (cur.min <= prev.max || cur.max <= prev.max) {
            prev = Interval(std::min(prev.min, cur.min), std::max(prev.max, cur.max));
        } else {
            merged.push_back(prev);
            prev = cur;
        }
        it++;
    }
    merged.push_back(prev);

    // Find the number of points covered on the row
    int sum = 0;
    for (const Interval &i : merged) {
        sum += i.max - i.min;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    vector<Sensor> sensors;
    stringstream ss; string s; char c;
    int sx, sy, bx, by, d;

    for (string &line : getlines(argc, argv)) {
        ss.clear(); ss.str(line);
        ss >> s >> s >> c >> c >> sx >> c >> c >> c >> sy;
        ss >> c >> s >> s >> s >> s >> c >> c >> bx >> c >> c >> c >> by;
        
        d = abs(bx - sx) + abs(by - sy);
        sensors.push_back(Sensor(sx, sy, d));
    }

    int x, y;
    for (x = 0; x <= 4000000; x++) {
        if (countPoints('x', x, sensors) < 4000000) break;
    }
    for (y = 0; y <= 4000000; y++) {
        if (countPoints('y', y, sensors) < 4000000) break;
    }    
    
    cout << "Part 1: " << countPoints('y', 2000000, sensors, false) << endl;
    cout << "Part 2: " << "x=" << x << ", y=" << y << endl;

    return 0;
}
