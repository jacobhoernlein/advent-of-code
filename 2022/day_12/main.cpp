#include <iostream>
#include <limits>
#include "vertex.h"
#include "jmch/getlines.h"

using namespace std;

void getGraph(vector<Vertex*> &graph, const vector<string> &lines,  Vertex* &start, Vertex* &end, char mode) {
    vector<vector<Vertex*>> matrix;
    Vertex *cur;
    
    // Create matrix of Vertex pointers. Store start and end.
    for (string line : lines) {
        matrix.push_back({});
        for (char h : line) {
            if (h == 'S') {
                start = new Vertex('a');
                matrix.back().push_back(start);
            } else if (h == 'E') {
                end = new Vertex('z');
                matrix.back().push_back(end);
            } else {
                matrix.back().push_back(new Vertex(h));
            }
        }
    }

    // Transform the matrix to an adjacency list.
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.at(i).size(); j++) {
            cur = matrix.at(i).at(j);
            
            vector<Vertex*> adjVs;
            // Add vertices corresponding to adjacent characters in input.
            if (i < matrix.size() - 1) adjVs.push_back(matrix.at(i + 1).at(j));
            if (i > 0) adjVs.push_back(matrix.at(i - 1).at(j));
            if (j < matrix.at(i).size() - 1) adjVs.push_back(matrix.at(i).at(j + 1));
            if (j > 0) adjVs.push_back(matrix.at(i).at(j - 1));

            // Check if actually traversable.
            for (Vertex* dest : adjVs) {
                if (mode == 'U' && cur->height >= dest->height - 1) {
                    cur->adjacentVertices.push_back(dest);
                }
                if (mode == 'D' && dest->height >= cur->height - 1) {
                    cur->adjacentVertices.push_back(dest);
                }
            }

            graph.push_back(cur);
        }
    }
}

void djikstras(const vector<Vertex*> &graph, Vertex* start) {
    VertexQueue unvisited;
    for (Vertex* v : graph) {
        v->dist = numeric_limits<int>{}.max();
        v->prev = nullptr;
        unvisited.push(v);
    }

    start->dist = 0;
    unvisited.percolateUp(start);

    Vertex *cur;
    int altDist;

    while (!unvisited.empty()) {
        cur = unvisited.pop();

        // Current node is unreachable.
        if (cur->dist == numeric_limits<int>{}.max()) return;

        for (Vertex* v : cur->adjacentVertices) {
            altDist = cur->dist + 1;
            if (altDist < v->dist) {
                v->dist = altDist;
                v->prev = cur;
                unvisited.percolateUp(v);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    vector<string> lines = getlines(argc, argv);
    
    vector<Vertex*> graph;
    Vertex *start, *end;
    
    getGraph(graph, lines, start, end, 'U');
    djikstras(graph, start);
    cout << "Part 1: " << end->dist << endl;

    for (Vertex* v : graph) {
        delete v;
    }
    graph.clear();
    
    getGraph(graph, lines, start, end, 'D');
    djikstras(graph, end);
    
    int minDist = numeric_limits<int>{}.max();
    for (Vertex* v : graph) {
        if (v->height == 'a' && v->dist < minDist) minDist = v->dist;
        delete v;
    }
    graph.clear();

    cout << "Part 2: " << minDist << endl;

    return 0;
}
