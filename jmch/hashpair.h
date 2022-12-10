#ifndef HASHPAIR_H_
#define HASHPAIR_H_

#include <functional>

// Hashes a std::pair. Modified from geeksforgeeks.
struct hash_pair {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        std::size_t hash1 = std::hash<T1>{}(p.first);
        std::size_t hash2 = std::hash<T2>{}(p.second);
        // Return bitwise XOR of hashes.
        return (hash1 == hash2) ? hash1 : hash1 ^ hash2;
    }
};

#endif
