#include "transform.h"

Transform::Transform()
	: position(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f), dimensions(200, 100) { }

Transform::Transform(Vector3& position, Vector3& scale, Vector3& rotation, Dimensions2& dimensions)
	: position(position), scale(scale), rotation(rotation), dimensions(dimensions) { }

// Setters
void Transform::setPosition(Vector3& position) {
	this->position = position;
}

void Transform::setRotation(Vector3& rotation) {
	this->rotation = rotation;
}

void Transform::setScale(Vector3& scale) {
	this->scale = scale;
}

// Getters
Vector3& Transform::getPosition() {
	return position;
}

Vector3& Transform::getRotation() {
	return rotation;
}

Vector3& Transform::getScale() {
	return scale;
}

Dimensions2& Transform::getDimensions() {
	return dimensions;
}

// Debugging
std::string Transform::toString() {
	std::ostringstream oss;
	oss << "Transform - Position: x: " << position.x << ", y: " << position.y << ", z: " << position.z
		<< " Rotation: x: " << rotation.x << ", y: " << rotation.y << ", z: " << rotation.z
		<< " Scale: x: " << scale.x << ", y: " << scale.y << ", z: " << scale.z
		<< " Dimensions: width: " << dimensions.width << ", height: " << dimensions.height;
	return oss.str();
}