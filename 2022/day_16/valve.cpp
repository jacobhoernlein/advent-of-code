#include <limits>
#include "valve.h"

using namespace std;

Valve::Valve(int r) {
    rate = r;
}

void dijkstras(const vector<Valve*> &graph, Valve* start) {
    ValveQueue unvisited;
    for (Valve* v : graph) {
        v->dist = numeric_limits<int>{}.max();
        unvisited.push(v);
    }

    start->dist = 0;
    unvisited.percolateUp(start);

    Valve *cur;
    int altDist;

    while (!unvisited.empty()) {
        cur = unvisited.pop();

        for (Valve* v : cur->tunnels) {
            altDist = cur->dist + 1;
            if (altDist < v->dist) {
                v->dist = altDist;
                unvisited.percolateUp(v);
            }
        }
    }
}

vector<Valve*> buildGraph(
    const vector<pair<string, vector<string>>> &names,
    const unordered_map<string, Valve*> &nameToValve) {

    vector<Valve*> valves;

    // Add pointers to each valve and consolidate pointers into vector.
    for (const pair<string, vector<string>> &p : names) {
        Valve* v = nameToValve.at(p.first);
        for (const string &s : p.second) {
            v->tunnels.push_back(nameToValve.at(s));
        }
        valves.push_back(v);
    }

    // Find the distance from each valve to each other valve.
    for (Valve* v1 : valves) {
        dijkstras(valves, v1);
        for (Valve* v2 : valves) {
            v1->dists[v2] = v2->dist;
        }
    }

    return valves;
}

void ValveQueue::percolateUp(int i) {
    for (int j = i; j > 0; j = (j - 1) / 2) {
        Valve* &cur = arr.at(j);
        Valve* &parent = arr.at((j - 1) / 2);
        if (parent->dist > cur->dist) swap(parent, cur);
        else break;
    }
}

void ValveQueue::percolateUp(Valve* v) {
    int i = 0;
    while (true) {
        if (i >= arr.size()) return; // Vertex not in heap.
        if (arr.at(i) == v) break;
        else i++;
    }
    percolateUp(i);
}

void ValveQueue::push(Valve* v) {
    arr.push_back(v);
    percolateUp(arr.size() - 1); // Percolate up from that index.
}

Valve* ValveQueue::pop() {
    swap(arr.front(), arr.back());
    Valve* minValve = arr.back(); arr.pop_back();

    // Percolate down the new first element.
    int i = 0, c1, c2, minIndex;
    while (i < arr.size()) {
        c1 = 2 * i + 1;
        c2 = c1 + 1;

        // First child is out of bounds; so is second child.
        if (c1 >= arr.size()) break;

        // Find index of minimum element between three
        minIndex = i;
        if (arr.at(c1)->dist < arr.at(minIndex)->dist) minIndex = c1;
        if (c2 < arr.size() && arr.at(c2)->dist < arr.at(minIndex)->dist) minIndex = c2;

        // Element has reached a good place in the heap.
        if (minIndex == i) break;

        // It hasn't. Swap the two and set index to index swapped with.
        swap(arr.at(i), arr.at(minIndex));
        i = minIndex;
    }

    return minValve;
}

bool ValveQueue::empty() const {
    return arr.empty();
}
