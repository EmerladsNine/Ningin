#pragma once

#include "Archetype.h"
#include <cstddef>
#include <vector>

using namespace std;

struct VectorHasher
{
	size_t operator()(const vector<ComponentId>& V) const {
		size_t hash = V.size();
		for (const auto& i : V) {
			hash ^= i.hash_code() + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}

		return hash;
	}
};
