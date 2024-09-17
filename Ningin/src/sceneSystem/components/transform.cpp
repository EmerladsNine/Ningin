#include "Transform.h"

Transform::Transform(Vector3& position, Vector3& scale, Vector3& rotation) : position(position),
	scale(scale), rotation(rotation) {}

Transform::Transform() : position(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f) {}

void TransformSetPosition(Transform& transform, Vector3& position)
{
	transform.position = position;
}

void TransformSetRotation(Transform& transform, Vector3& rotation)
{
	transform.rotation = rotation;
}

void TransformSetScale(Transform& transform, Vector3& scale)
{
	transform.scale = scale;
}

void TransformGetPosition(Transform& transform, Vector3& out)
{
	out = transform.position;
}

void TransformGetRotation(Transform& transform, Vector3& out)
{
	out = transform.rotation;
}

void TransformGetScale(Transform& transform, Vector3& out) {
	out = transform.scale;
}

void TransformToString(Transform& transform, string& out)
{
	out = format("Transform - Position: x: {}, y: {}, z: {}\nRotation: x: {}, y: {}, z: {}\nScale: x: {}, y: {}, z: {}",
		transform.position.x, transform.position.y, transform.position.z, transform.rotation.x,
		transform.rotation.y, transform.rotation.z, transform.scale.x, transform.scale.y, transform.scale.z);
}
