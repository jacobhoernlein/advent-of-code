#ifndef HASHPAIR_H_
#define HASHPAIR_H_

#include<unordered_map>
#include <utility>

// Hashes a std::pair.
struct hash_pair {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        // All this was stolen from geeksforgeeks lol.
        std::size_t hash1 = std::hash<T1>{}(p.first);
        std::size_t hash2 = std::hash<T2>{}(p.second);
    
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
            
        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

#endif
