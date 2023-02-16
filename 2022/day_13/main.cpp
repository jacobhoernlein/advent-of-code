#include <algorithm>
#include <iostream>
#include "packet.h"
#include "jmch/getlines.h"

using namespace jmch;
using namespace std;

int main(int argc, char* argv[]) {
    vector<string> lines = getlines(argc, argv);
    vector<Packet> packets;
    int sum = 0;

    for (int i = 0; i < lines.size(); i += 3) {
        packets.push_back(Packet(lines.at(i)));
        packets.push_back(Packet(lines.at(i + 1)));
        if (*(&packets.back() - 1) < packets.back()) sum += i / 3 + 1;
    }

    packets.push_back(Packet("[[2]]")); int d1 = 0;
    packets.push_back(Packet("[[6]]")); int d2 = 0;

    sort(packets.begin(), packets.end());
    for (int i = 0; i < packets.size(); i++) {
        if (packets.at(i) == "[[2]]") d1 = i + 1;
        if (packets.at(i) == "[[6]]") d2 = i + 1;
    }

    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << d1 * d2 << endl;

    return 0;
}
