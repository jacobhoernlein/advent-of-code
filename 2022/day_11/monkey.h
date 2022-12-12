#ifndef MONKEY_H_
#define MONKEY_H_

#include <functional>
#include <queue>
#include <vector>

class Monkey {
    std::queue<int> items;
    int numInspected;

    std::function<int(int)> operation;
    int divisor;

    int trueDestDif;
    int falseDestDif;
public:
    Monkey(const std::vector<int> &startingItems, std::function<int(int)> operation, int divisor, int trueDestDif, int falseDestDif);
    void lookAtItems_pt1();
    void lookAtItems_pt2();
    int getNumInspected() const;
};

#endif
