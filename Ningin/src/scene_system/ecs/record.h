#pragma once
#include "archetype.h"
class Record
{
public:
	Archetype* archetype_ptr;
	size_t row;
	Record(Archetype* archetype_ptr, std::size_t row);
};
