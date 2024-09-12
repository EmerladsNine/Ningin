#pragma once

#include "Archetype.h"

class Record
{
	public:
		Record(Archetype* archetypePtr, std::size_t row);

		Archetype* archetypePtr;
		size_t row;
};
