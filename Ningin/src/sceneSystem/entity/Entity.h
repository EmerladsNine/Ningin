#pragma once
#include "../components/Transform.h"
#include "../../ningin.h"

void EntityGetTransform(EntityId entityId, Transform** transform);

void EntitySetTransform(EntityId entityId, Transform** transform);

bool EntityHasComponent(EntityId entityId, MonoReflectionType* type);

void EntityGetComponent(EntityId entityId, MonoReflectionType* type,void** data);