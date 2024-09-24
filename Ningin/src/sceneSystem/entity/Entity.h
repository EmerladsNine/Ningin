#pragma once
#include "../components/Transform.h"
#include "../../ningin.h"

void EntityGetTransform(EntityId entityId, Transform** transform);

void EntitySetTransform(EntityId entityId, Transform** transform);