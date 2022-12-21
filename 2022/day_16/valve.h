#ifndef VALVE_H_
#define VALVE_H_

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Valve {
    int rate;
    std::unordered_map<Valve*, int> dists; // Stores distance for each other valve.

    Valve(int r);

    std::vector<Valve*> tunnels; // For use when building graph
    int dist; // For use in djikstras
};

void dijkstras(const std::vector<Valve*> &graph, Valve* start);

std::vector<Valve*> buildGraph(
    const std::vector<std::pair<std::string, std::vector<std::string>>> &names,
    const std::unordered_map<std::string, Valve*> &nameToValve);

struct ValveQueue {
    std::vector<Valve*> arr; 
    void percolateUp(int i);
    void percolateUp(Valve* v);
    void push(Valve *v);
    Valve* pop();
    bool empty() const;
};

#endif
