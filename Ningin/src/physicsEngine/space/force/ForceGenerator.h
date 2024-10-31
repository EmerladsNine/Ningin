#pragma once
#include "../Pointmass.h"
#include "../Time.h"

namespace Ningin::Physics
{
	class ForceGenerator
	{
	public:
		void updateForces(Pointmass* pointmass, Time duration);
	};
}