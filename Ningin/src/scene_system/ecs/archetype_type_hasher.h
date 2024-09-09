#pragma once
#include "archetype.h"
#include <cstddef>
#include <vector>

struct VectorHasher
{
	std::size_t operator()(const std::vector<ComponentId>& V) const
	{
		std::size_t hash = V.size();
		for (const auto& i : V)
		{
			hash ^= i.hash_code() + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}
		return hash;
	}
};
