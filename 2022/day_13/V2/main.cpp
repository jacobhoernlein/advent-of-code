#include <algorithm>
#include <iostream>
#include "packet.h"
#include "jmch/getlines.h"
#include "jmch/List.cpp"

using namespace jmch;
using namespace std;

int main(int argc, char* argv[]) {
    List<string> lines(getlines(argc, argv));
    List<Packet> packets;

    int sum = 0;

    for (int i = 0; i < lines.length(); i += 3) {
        packets.pushBack(Packet(lines[i]));
        packets.pushBack(Packet(lines[i + 1]));
        if (packets[-2] < packets[-1]) sum += i / 3 + 1;
    }

    packets.pushBack(Packet("[[2]]")); int d1 = 0;
    packets.pushBack(Packet("[[6]]")); int d2 = 0;

    sort(packets.begin(), packets.end());
    for (int i = 0; i < packets.length(); i++) {
        if (packets[i] == "[[2]]") d1 = i + 1;
        if (packets[i] == "[[6]]") d2 = i + 1;
    }

    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << d1 * d2 << endl;

    return 0;
}
