#include "monkey.h"

using namespace std;

Monkey::Monkey(const vector<int> &startingItems, function<int(int)> operation, int divisor, int trueDestDif, int falseDestDif) {
    for (int element : startingItems) {
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
        curItem = operation(curItem);
        (this + ((curItem % divisor == 0) ? trueDestDif : falseDestDif))->items.push(curItem % 9699690);
    }
}

int Monkey::getNumInspected() const {
    return numInspected;
}
