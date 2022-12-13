#ifndef MONKEY_H_
#define MONKEY_H_

#include <functional>
#include <queue>
#include <vector>

class Monkey {
    std::queue<u_int64_t> items;
    int numInspected;

    std::function<u_int64_t(u_int64_t)> operation;
    int divisor;

    int trueDestDif;
    int falseDestDif;
public:
    Monkey(const std::vector<u_int64_t> &startingItems, std::function<u_int64_t(u_int64_t)> operation, int divisor, int trueDestDif, int falseDestDif);
    void lookAtItems_pt1();
    void lookAtItems_pt2();
    int getNumInspected() const;
};

#endif
