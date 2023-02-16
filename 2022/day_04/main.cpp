#include <iostream>
#include <sstream>
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

int encapsulation(const string &s) {
    int s1, e1, s2, e2; char d;
    stringstream ss(s);
    ss >> s1 >> d >> e1 >> d >> s2 >> d >> e2;
    return ((s2 >= s1 && e2 <= e1) || (s2 <= s1 && e2 >= e1)) ? 1 : 0;
}

int overlap(const string &s) {
    int s1, e1, s2, e2; char d;
    stringstream ss(s);
    ss >> s1 >> d >> e1 >> d >> s2 >> d >> e2;
    return ((s2 >= s1 && s2 <= e1) || (s1 >= s2 && s1 <= e2)) ? 1 : 0;
}

int main(int argc, char* argv[]) {
    int sum1 = 0, sum2 = 0;
    
    for (string line : getlines(argc, argv)) {        
        sum1 += encapsulation(line);
        sum2 += overlap(line);
    }

    cout << "Part 1: " << sum1 << endl;
    cout << "Part 2: " << sum2 << endl;

    return 0;
}
