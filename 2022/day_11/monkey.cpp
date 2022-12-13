#include "monkey.h"

using namespace std;

Monkey::Monkey(const std::vector<u_int64_t> &startingItems, std::function<u_int64_t(u_int64_t)> operation, int divisor, int trueDestDif, int falseDestDif) {
    for (u_int64_t element : startingItems) {
        this->items.push(element);
    }
    this->numInspected = 0;
    this->operation = operation;
    this->divisor = divisor;
    this->trueDestDif = trueDestDif;
    this->falseDestDif = falseDestDif;
}

void Monkey::lookAtItems_pt1() {
    int curItem;
    while (!items.empty()) {
        numInspected++;
        curItem = items.front(); items.pop();
        curItem = operation(curItem);
        curItem /= 3;
        (this + ((curItem % divisor == 0) ? trueDestDif : falseDestDif))->items.push(curItem);

    }
}

void Monkey::lookAtItems_pt2() {
    int curItem;
    while (!items.empty()) {
        numInspected++;
        curItem = items.front(); items.pop();
        curItem = operation(curItem) % 9699690;
        (this + ((curItem % divisor == 0) ? trueDestDif : falseDestDif))->items.push(curItem);
    }
}

int Monkey::getNumInspected() const {
    return numInspected;
}
