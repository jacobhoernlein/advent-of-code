#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

class Rope {
    std::pair<int, int> head;
    std::vector<std::pair<int, int>> tail;
    
    std::unordered_set<std::string> visitedPoints;
public:
    // Initialize rope with given length.
    Rope(int length);
    
    // Move head of the rope as directed. Also moves the tail.
    void moveHead(char direction, int count);
    // Return the number of distinct points visited by the end of the rope.
    int getVisitedPoints();
};
