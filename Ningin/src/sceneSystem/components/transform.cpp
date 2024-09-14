#include "Transform.h"

Transform::Transform() : _position(0.0f, 0.0f, 0.0f), _scale(1.0f, 1.0f, 1.0f), _rotation(0.0f, 0.0f, 0.0f),
	_dimensions(200, 100) {}

Transform::Transform(Vector3& position, Vector3& scale, Vector3& rotation, Dimensions2& dimensions)
	: _position(position), _scale(scale), _rotation(rotation), _dimensions(dimensions) {}

void Transform::SetPosition(Vector3& position)
{
	this->_position = position;
}

void Transform::SetRotation(Vector3& rotation)
{
	this->_rotation = rotation;
}

void Transform::SetScale(Vector3& scale)
{
	this->_scale = scale;
}

Vector3& Transform::GetPosition()
{
	return _position;
}

Vector3& Transform::GetRotation()
{
	return _rotation;
}

Vector3& Transform::GetScale()
{
	return _scale;
}

Dimensions2& Transform::GetDimensions()
{
	return _dimensions;
}

// Debugging
string Transform::ToString()
{
	return format("Transform - Position: x: {}, y: {}, z: {}\nRotation: x: {}, y: {}, z: {}\nScale: x: {}, y: {}, z: {}\nDimensions: width: {}, height {}",
		_position.x, _position.y, _position.z, _rotation.x, _rotation.y, _rotation.z, _scale.x, _scale.y,
		_scale.z,_dimensions.width, _dimensions.height);
}
