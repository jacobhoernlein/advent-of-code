#include <iostream>
#include "cpu.h"

using namespace std;

CPU::CPU() {
    x = 1;
    cycle = 0;
    strengths = vector(1, 0);
    screen = vector(6, string(40, '.'));
}

void CPU::fireCRT() {
    int CRTx = (cycle - 1) % 40;
    int CRTy = (cycle - 1) / 40;
    if (CRTx >= (x - 1) && CRTx <= (x + 1))
        screen.at(CRTy).at(CRTx) = '#';
}

void CPU::addx(int v) {
    cycle++;
    strengths.push_back(cycle * x);
    fireCRT();

    cycle++;
    strengths.push_back(cycle * x);
    fireCRT();

    x += v;
}

void CPU::noop() {
    cycle++;
    strengths.push_back(cycle * x);
    fireCRT();
}

int CPU::sumStrengths() {
    int sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += strengths.at(20 + (40 * i));
    }
    return sum;
}

void CPU::printScreen() {
    for (string row : screen) {
        cout << row << "\n";
    }
}
