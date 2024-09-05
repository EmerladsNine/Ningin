#pragma once
#include <cstddef>
#include <vector>
#include "archetype.h"

struct VectorHasher {
    std::size_t operator()(const std::vector<ComponentId>& V) const {
        std::size_t hash = V.size();
        for (const auto& i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};
