#pragma once

#include <cstddef>

using namespace std;

class Archetype; // Forward declaration of Archetype class

class ArchetypeRecord {
	public:
		ArchetypeRecord(Archetype* archetype, size_t column);

		Archetype* archetype;
		size_t column;
};
