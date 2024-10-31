#pragma once
#include "../components/Transform.h"
#include "../../ningin.h"

namespace Ningin::Components
{
	bool EntityHasComponent(EntityId entityId, MonoReflectionType* type);

	void EntityGetComponent(EntityId entityId, MonoReflectionType* type, void** data);
}