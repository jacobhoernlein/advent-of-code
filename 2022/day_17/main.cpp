#include <iostream>
#include <numeric>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

typedef pair<u_int64_t, u_int64_t> Point;

struct Block {
    Point origin;
    vector<Point> pointDists;
    int height;

    Block(const Point &p, int type);
    vector<Point> points();

    bool collides(const vector<string> &map);
};

Block::Block(const Point &p, int type) {
    origin = p;
    switch (type) {
        case 0:
            pointDists = {pair(0, 0), pair(1, 0), pair(2, 0), pair(3, 0)};
            height = 1;
            break;
        case 1:
            pointDists = {pair(1, 0), pair(0, 1), pair(1, 1), pair(2, 1), pair(1, 2)};
            height = 3;
            break;
        case 2:
            pointDists = {pair(0, 0), pair(1, 0), pair(2, 0), pair(2, 1), pair(2, 2)};
            height = 3;
            break;
        case 3:
            pointDists = {pair(0, 0), pair(0, 1), pair(0, 2), pair(0, 3)};
            height = 4;
            break;
        case 4:
            pointDists = {pair(0, 0), pair(1, 0), pair(0, 1), pair(1, 1)};
            height = 2;
            break;
    }
}

vector<Point> Block::points() {
    vector<Point> points = pointDists;
    for (Point &point : points) {
        point.first += origin.first;
        point.second += origin.second;
    }
    return points;
}

bool Block::collides(const vector<string> &map){
    for (const Point &point : points()) {
        if (map.at(point.second).at(point.first) != '.') return true;
    }
    return false;
}

u_int64_t part1(const string &directions, const u_int64_t numBlocks) {
    int i = 0; // floor is at 0
    u_int64_t prev = 0;
    vector<string> map = vector(1, string("|-------|"));

    for (u_int64_t n = 0; n < numBlocks; n++) {
                
        Block block(Point(3, prev + 4), n % 5);
        for (size_t j = map.size(); j < prev + 4 + block.height; j++)
            map.push_back(string("|.......|"));
        
        while (true) {
            
            if (directions.at(i) == '<') {
                block.origin.first--;
                if (block.collides(map)) block.origin.first++;
            } else {
                block.origin.first++;
                if (block.collides(map)) block.origin.first--;
            }
            i = (i + 1) % directions.size();

            block.origin.second--;
            if (block.collides(map)) {
                block.origin.second++;

                for (const Point &point : block.points()) {
                    map.at(point.second).at(point.first) = n % 5 + '1';
                }
               
                prev = max(prev, block.origin.second + block.height - 1);
                break;
            }
        }
    }
    vector<string>::iterator it;
    for (it = map.end(); it >= map.begin(); it--) {
        cout << *it << "\n";
    }
    return prev;
}

int main(int argc, char* argv[]) {
    string directions = getlines(argc, argv)[0];

    // cout << "Part 1: " << part1(directions, 2022) << endl;

    const u_int64_t numBlocks = 1000000000000;
    const u_int64_t lcm = std::lcm(directions.size(), 5);

    const u_int64_t nums = numBlocks / lcm;
    const u_int64_t nums2 = numBlocks % lcm;

    cout << part1(directions, lcm) << endl;;

    // u_int64_t p2 = nums * part1(directions, lcm) + part1(directions, nums2);
    // cout << "Part 2: " << p2 << endl;

    return 0;
}
