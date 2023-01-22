#ifndef CPU_H_
#define CPU_H_

#include <string>
#include <vector>

class CPU {
    int x;
    int cycle;
    std::vector<int> strengths;
    std::vector<std::string> screen;
    void fireCRT();
public:
    CPU();
    void addx(int v);
    void noop();
    void doCycle(const int num = 1);
    int sumStrengths();
    void printScreen();
};

#endif
