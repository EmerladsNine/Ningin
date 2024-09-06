#pragma once
class Archetype; // Forward declaration of Archetype class

class ArchetypeEdge
{
public:
	Archetype* add;
	Archetype* rmv;
	ArchetypeEdge();
};
