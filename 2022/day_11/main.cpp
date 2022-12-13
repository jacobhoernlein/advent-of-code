#include <algorithm>
#include <iostream>
#include "monkey.h"

using namespace std;

u_int64_t monkey0op(u_int64_t old) {
    return old * 17;
}

u_int64_t monkey1op(u_int64_t old) {
    return old + 8;
}

u_int64_t monkey2op(u_int64_t old) {
    return old + 6;
}

u_int64_t monkey3op(u_int64_t old) {
    return old * 19;
}

u_int64_t monkey4op(u_int64_t old) {
    return old + 7;
}

u_int64_t monkey5op(u_int64_t old) {
    return old * old;
}

u_int64_t monkey6op(u_int64_t old) {
    return old + 1;
}

u_int64_t monkey7op(u_int64_t old) {
    return old + 2;
}

bool CompareMonkeys(const Monkey &m1, const Monkey &m2) {
    return (m1.getNumInspected() < m2.getNumInspected());
}

int main(int argc, char* argv[]) {
    vector<Monkey> monkeys1 = {
        Monkey({52, 60, 85, 69, 75, 75}, monkey0op, 13, 6, 7),
        Monkey({96, 82, 61, 99, 82, 84, 85}, monkey1op, 7, -1 ,6),
        Monkey({95, 79}, monkey2op, 19, 3, 1),
        Monkey({88, 50, 82, 65, 77}, monkey3op, 2, 1, -2),
        Monkey({66, 90, 59, 90, 87, 63, 53, 88}, monkey4op, 5, -3, -4),
        Monkey({92, 75, 62}, monkey5op, 3, -2, -1),
        Monkey({94, 86, 76, 67}, monkey6op, 11, -1, -4),
        Monkey({57}, monkey7op, 17, -1, -5)
    };
    vector<Monkey> monkeys2 = {
        Monkey({52, 60, 85, 69, 75, 75}, monkey0op, 13, 6, 7),
        Monkey({96, 82, 61, 99, 82, 84, 85}, monkey1op, 7, -1 ,6),
        Monkey({95, 79}, monkey2op, 19, 3, 1),
        Monkey({88, 50, 82, 65, 77}, monkey3op, 2, 1, -2),
        Monkey({66, 90, 59, 90, 87, 63, 53, 88}, monkey4op, 5, -3, -4),
        Monkey({92, 75, 62}, monkey5op, 3, -2, -1),
        Monkey({94, 86, 76, 67}, monkey6op, 11, -1, -4),
        Monkey({57}, monkey7op, 17, -1, -5)
    };
    
    for (int i = 0; i < 20; i++) {
        for (Monkey &monkey : monkeys1) {
            monkey.lookAtItems_pt1();
        }
    }

    for (int i = 0; i < 10000; i++) {
        for (Monkey &monkey : monkeys2) {
            monkey.lookAtItems_pt2();
        }
    }

    sort(monkeys1.begin(), monkeys1.end(), CompareMonkeys);
    int part1 = monkeys1.back().getNumInspected(); monkeys1.pop_back();
    part1 *= monkeys1.back().getNumInspected();
    cout << "Part 1: " << part1 << endl;

    sort(monkeys2.begin(), monkeys2.end(), CompareMonkeys);    
    unsigned long long int part2 = monkeys2.back().getNumInspected(); monkeys2.pop_back();
    part2 *= monkeys2.back().getNumInspected();
    cout << "Part 2: " << part2 << endl;

    return 0;
}
