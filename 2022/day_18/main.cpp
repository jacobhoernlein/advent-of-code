#include <iostream>
#include <sstream>
#include <queue>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

typedef vector<vector<vector<bool>>> Map;

int getSurfaceArea(const Map &map) {
    int area = 0;
    for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map.at(x).size(); y++) {
            for (int z = 0; z < map.at(x).at(y).size(); z++) {
                if (map.at(x).at(y).at(z)) {
                    try {if (!map.at(x + 1).at(y).at(z)) area++;} 
                    catch (const out_of_range &e) {area++;}

                    try {if (!map.at(x - 1).at(y).at(z)) area++;} 
                    catch (const out_of_range &e) {area++;}
                    
                    try {if (!map.at(x).at(y + 1).at(z)) area++;} 
                    catch (const out_of_range &e) {area++;}

                    try {if (!map.at(x).at(y - 1).at(z)) area++;} 
                    catch (const out_of_range &e) {area++;}

                    try {if (!map.at(x).at(y).at(z + 1)) area++;} 
                    catch (const out_of_range &e) {area++;}

                    try {if (!map.at(x).at(y).at(z - 1)) area++;} 
                    catch (const out_of_range &e) {area++;}
                }
            }
        }
    }
    return area;
}

struct Block {
    int x;
    int y;
    int z;
    Block(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

int getSurfaceArea_pt2(const Map &inputMap) {
    int area = 0;

    Map seen(22, vector(22, vector(22, false))); // Scan around perimeter
    queue<Block> q;
    q.push(Block(0, 0, 0));


    Map map(22, vector(22, vector(22, false)));
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            for (int z = 0; z < 20; z++) {
                map.at(x + 1).at(y + 1).at(z + 1) = inputMap.at(x).at(y).at(z);
            }
        }
    }

    while (!q.empty()) {
        Block b = q.front(); q.pop();

        try {
            if (map.at(b.x + 1).at(b.y).at(b.z)) {
                area++;
            } else if (!seen.at(b.x + 1).at(b.y).at(b.z)) {
                q.push(Block(b.x + 1, b.y, b.z));
                seen.at(b.x + 1).at(b.y).at(b.z) = true;
            }
        } 
        catch (const out_of_range &e) {}

        try {
            if (map.at(b.x - 1).at(b.y).at(b.z)) {
                area++;
            } else if (!seen.at(b.x - 1).at(b.y).at(b.z)) {
                q.push(Block(b.x - 1, b.y, b.z));
                seen.at(b.x - 1).at(b.y).at(b.z) = true;
            }
        } 
        catch (const out_of_range &e) {}

        try {
            if (map.at(b.x).at(b.y + 1).at(b.z)) {
                area++;
            } else if (!seen.at(b.x).at(b.y + 1).at(b.z)) {
                q.push(Block(b.x, b.y + 1, b.z));
                seen.at(b.x).at(b.y + 1).at(b.z) = true;
            }
        } 
        catch (const out_of_range &e) {}

        try {
            if (map.at(b.x).at(b.y - 1).at(b.z)) {
                area++;
            } else if (!seen.at(b.x).at(b.y - 1).at(b.z)) {
                q.push(Block(b.x, b.y - 1, b.z));
                seen.at(b.x).at(b.y - 1).at(b.z) = true;
            }
        } 
        catch (const out_of_range &e) {}

        try {
            if (map.at(b.x).at(b.y).at(b.z + 1)) {
                area++;
            } else if (!seen.at(b.x).at(b.y).at(b.z + 1)) {
                q.push(Block(b.x, b.y, b.z + 1));
                seen.at(b.x).at(b.y).at(b.z + 1) = true;
            }
        } 
        catch (const out_of_range &e) {}

        try {
            if (map.at(b.x).at(b.y).at(b.z - 1)) {
                area++;
            } else if (!seen.at(b.x).at(b.y).at(b.z - 1)) {
                q.push(Block(b.x, b.y, b.z - 1));
                seen.at(b.x).at(b.y).at(b.z - 1) = true;
            }
        } 
        catch (const out_of_range &e) {}
    }
    return area;
}

int main(int argc, char* argv[]) {
    Map map(20, vector(20, vector(20, false)));

    for (string line : getlines(argc, argv)) {
        stringstream ss(line); 
        int x, y, z; char d;

        ss >> x >> d >> y >> d >> z;
        map.at(x).at(y).at(z) = true;
    }

    cout << "Part 1: " << getSurfaceArea(map) << endl;
    cout << "Part 2: " << getSurfaceArea_pt2(map) << endl;

    return 0;
}
