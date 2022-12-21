#include <iostream>
#include <sstream>
#include "valve.h"
#include "jmch/getlines.h"

using namespace std;

int findMax_pt1(
        const vector<Valve*> &closed,
        Valve* curValve, const int curMin) {
    
    int maxVal = 0;
    
    // We only want to target closed valves.
    for (Valve* v : closed) {
        const int nextMin = curMin + curValve->dists[v] + 1; 

        // No use going to valve if it won't add to rate.
        if (v->rate <= 0 || nextMin > 30) continue;

        vector<Valve*> nextClosed;
        for (Valve* v2 : closed) {
            if (v2 != v) nextClosed.push_back(v2);
        }

        // Recursively find max for next block.
        const int val = 
            (v->rate * (31 - nextMin))
            + findMax_pt1(nextClosed, v, nextMin);

        maxVal = max(val, maxVal);
    }
    return maxVal;
}

int findMax_pt2(
        const vector<Valve*> &closed,
        Valve* eCurValve, Valve* mCurValve,
        const int eCurMin, const int mCurMin) {
    
    int maxVal = 0;

    for (Valve* ev : closed) {
        const int eNextMin = eCurMin + eCurValve->dists[ev] + 1; 
        if (ev->rate <= 0 || eNextMin > 26) continue;

        vector<Valve*> eNextClosed;
        for (Valve* v : closed) {
            if (v != ev) eNextClosed.push_back(v);
        }

        for (Valve* mv : eNextClosed) {
            const int mNextMin = mCurMin + mCurValve->dists[mv] + 1; 
            if (mv->rate <= 0 || mNextMin > 26) continue;

            vector<Valve*> mNextClosed;
            for (Valve* v : eNextClosed) {
                if (v != mv) mNextClosed.push_back(v);
            }

            const int val = 
                (ev->rate * (27 - eNextMin)) + (mv->rate * (27 - mNextMin))
                + findMax_pt2(mNextClosed, ev, mv, eNextMin, mNextMin);
        
            maxVal = max(val, maxVal);
        }
    }
    return maxVal;
}

int main(int argc, char* argv[]) {
    vector<pair<string, vector<string>>> names;
    unordered_map<string, Valve*> nameToValve;

    for (string line : getlines(argc, argv)) {
        stringstream ss(line);
        string name, s; 
        int rate; char c;

        ss >> s >> name >> s >> s >> c >> c >> c >> c >> c;
        ss >> rate >> c >> s >> s >> s >> s;

        names.push_back(pair<string, vector<string>>(name, {}));
        nameToValve[name] = new Valve(rate);

        while (!ss.eof()) {
            ss >> s;
            names.back().second.push_back(s.substr(0, 2));
        }
    }

    vector<Valve*> valves = buildGraph(names, nameToValve);
    Valve* start = nameToValve["AA"];

    cout << "Part 1: " << findMax_pt1(valves, start, 1) << endl;
    cout << "Part 2: " << findMax_pt2(valves, start, start, 1, 1) << endl;

    return 0;
}
