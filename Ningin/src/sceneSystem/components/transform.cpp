#include "Transform.h"

Transform::Transform() : position(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f),
dimensions(200, 100) {}

Transform::Transform(Vector3& position, Vector3& scale, Vector3& rotation, Dimensions2& dimensions)
	: position(position), scale(scale), rotation(rotation), dimensions(dimensions) {}

void Transform::SetPosition(Vector3& position)
{
	this->position = position;
}

void Transform::SetRotation(Vector3& rotation)
{
	this->rotation = rotation;
}

void Transform::SetScale(Vector3& scale)
{
	this->scale = scale;
}

Vector3& Transform::GetPosition()
{
	return position;
}

Vector3& Transform::GetRotation()
{
	return rotation;
}

Vector3& Transform::GetScale()
{
	return scale;
}

Dimensions2& Transform::GetDimensions()
{
	return dimensions;
}

// Debugging
string Transform::ToString()
{
	return format("Transform - Position: x: {}, y: {}, z: {}\nRotation: x: {}, y: {}, z: {}\nScale: x: {}, y: {}, z: {}\nDimensions: width: {}, height {}",
		position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z,
		dimensions.width, dimensions.height);
}
