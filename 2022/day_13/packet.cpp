#include <ctype.h>
#include "packet.h"

using namespace std;

Packet::Packet(Packet* parent) {
    this->parent = parent;
    value = 0;
    isInt = false;
}

Packet::Packet(Packet* parent, int value) {
    this->parent = parent;
    this->value = value;
    isInt = true;
}

Packet::Packet(string line) {
    parent = nullptr;
    value = 0;
    isInt = false;

    Packet* cur = this;
    for (int i = 1; i < line.size() - 1; i++) {
        if (line.at(i) == '[') {
            cur->children.push_back(Packet(cur));
            cur = &cur->children.back();
        }
        else if (line.at(i) == ']') {
            cur = cur->parent;
        }
        else if (line.at(i) == ',') {
            continue;
        }
        else {
            cur->children.push_back(Packet(cur, stoi(line.substr(i))));
            while (isdigit(line.at(i + 1))) i++;
        }
    }
}

int operator<(Packet &left, Packet &right) {
    // Both integers, compare directly.
    if (left.isInt && right.isInt) {
        if (left.value < right.value) return packetLessThan::yes;
        if (left.value > right.value) return packetLessThan::no;
        return packetLessThan::undetermined;
    }
    // Both lists, compare each value.
    else if (!left.isInt && !right.isInt) {
        for (int i = 0, j = 0; i < left.children.size() && j < right.children.size(); i++, j++) {
            int res = left.children.at(i) < right.children.at(j);
            if (res != packetLessThan::undetermined) return res;
        }
        if (left.children.size() < right.children.size()) return packetLessThan::yes;
        if (left.children.size() > right.children.size()) return packetLessThan::no;
        return packetLessThan::undetermined;
    }
    // One is list, one is int. Convert int to list.
    else {
        if (left.isInt) {
            left.children.push_back(Packet(&left, left.value));
            left.isInt = false;
        }
        if (right.isInt) {
            right.children.push_back(Packet(&right, right.value));
            right.isInt = false;
        }
        return left < right;
    }
}

bool operator==(Packet &left, const string &line) {
    Packet right(line);
    return (left < right) == packetLessThan::undetermined;
}
