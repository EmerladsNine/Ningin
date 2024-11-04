#include "GravityForceGenerator.h"
#include "../space/Pointmass.h"

namespace Ningin::Physics
{

	GravityForceGenerator::GravityForceGenerator() : gravity(0)
	{
	}

	GravityForceGenerator::GravityForceGenerator(float gravity) : gravity(gravity)
	{
	}

	void GravityForceGenerator::System(float deltatime, ArchetypeManager& archetypeManager)
	{
		auto& pointmassArchetypeMap = archetypeManager.componentIndex[typeid(Pointmass)];
		for (auto& generatorArchetype : archetypeManager.componentIndex[typeid(GravityForceGenerator)])
		{
			auto it = pointmassArchetypeMap.find(generatorArchetype.first);

			if (it != pointmassArchetypeMap.end())
			{
				size_t generatorColumn = generatorArchetype.second.column;
				size_t pointmassColumn = it->second.column;
				int row = 0;

				for (void* generatorData : generatorArchetype.second.archetype->components[generatorColumn])
				{
					if (generatorData == nullptr)
					{
						continue;
					}

					void* pointmassData = generatorArchetype.second.archetype->components[pointmassColumn][row];

					if (pointmassData == nullptr)
					{
						continue;
					}

					GravityForceGenerator* generator = static_cast<GravityForceGenerator*>(generatorData);
					Pointmass* pointmass = static_cast<Pointmass*>(pointmassData);

					

					row++;
				}
			}
		}
	}

}
