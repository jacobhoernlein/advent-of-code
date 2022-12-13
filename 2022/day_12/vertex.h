#ifndef VERTEX_H_
#define VERTEX_H_

#include <functional>
#include <utility>
#include <vector>

struct Vertex {
    char height;
    std::vector<Vertex*> adjacentVertices;
    Vertex* prev;
    int dist;

    Vertex(char h);
};

struct VertexQueue {
    std::vector<Vertex*> arr; 
    void percolateUp(int i);
    void percolateUp(Vertex* v);
    void push(Vertex *v);
    Vertex* pop();
    bool empty() const;
};

#endif
