#include <limits>
#include "vertex.h"

using namespace std;

Vertex::Vertex(char h) {
    height = h;
    prev = nullptr;
    dist = numeric_limits<int>{}.max();
}

void VertexQueue::percolateUp(int i) {    
    for (int j = i; j > 0; j = (j - 1) / 2) {
        Vertex* &cur = arr.at(j);
        Vertex* &parent = arr.at((j - 1) / 2);
        if (parent->dist > cur->dist) swap(parent, cur);
        else break;
    }
}

void VertexQueue::percolateUp(Vertex* v) {
    int i = 0;
    while (true) {
        if (i >= arr.size()) return; // Vertex not in heap.
        if (arr.at(i) == v) break;
        else i++;
    }
    percolateUp(i);
}

void VertexQueue::push(Vertex* v) {
    arr.push_back(v);
    percolateUp(arr.size() - 1); // Percolate up from that index.
}

Vertex* VertexQueue::pop() {
    swap(arr.front(), arr.back());
    Vertex* minVertex = arr.back(); arr.pop_back();
    
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
    
    return minVertex;
}

bool VertexQueue::empty() const {
    return arr.empty();
}
