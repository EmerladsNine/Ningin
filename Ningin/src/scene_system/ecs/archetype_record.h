#pragma once
#include<cstddef>

class Archetype; // Forward declaration of Archetype class
class ArchetypeRecord
{
public:
	Archetype* archetype;
	std::size_t column;
	ArchetypeRecord(Archetype* archetype,std::size_t column);
};