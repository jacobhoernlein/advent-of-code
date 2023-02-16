#ifndef PACKET_H_
#define PACKET_H_

#include <string>
#include "jmch/List.cpp"

enum packetLessThan {
    undetermined = -1,
    no = 0,
    yes = 1,
};

class Packet {
    jmch::List<Packet> children;
    Packet* parent;
    int value;
    bool isInt;

    Packet(Packet* parent);
    Packet(Packet* parent, int value);
public:
    Packet();
    Packet(std::string line);

    friend int operator<(Packet &left, Packet &right);
    friend bool operator==(Packet &left, const std::string &line);
};

#endif
