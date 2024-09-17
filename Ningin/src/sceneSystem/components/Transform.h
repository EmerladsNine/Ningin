#pragma once

#include "../../math/Dimensions2.h"
#include "../../math/Vector3.h"
#include <format>

using namespace std;

class Transform
{
	public:
		Transform(Vector3& position, Vector3& scale, Vector3& rotation);
		Transform();

		Vector3 position;
		Vector3 scale;
		Vector3 rotation;
};

void TransformSetPosition(Transform& transform, Vector3& position);
void TransformSetRotation(Transform& transform, Vector3& rotation);
void TransformSetScale(Transform& transform, Vector3& scale);

void TransformGetPosition(Transform& transform, Vector3& out);
void TransformGetRotation(Transform& transform, Vector3& out);
void TransformGetScale(Transform& transform, Vector3& out);

void TransformToString(Transform& transform, string& out);
