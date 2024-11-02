#pragma once

class Archetype; // Forward declaration of Archetype class

class ArchetypeEdge
{
	public:
		ArchetypeEdge();

		Archetype* add;
		Archetype* rmv;
};
