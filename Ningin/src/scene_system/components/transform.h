#pragma once

#include "../../math/dimensions2.h"
#include "../../math/vector3.h"
#include <sstream>

class Transform
{
public:
	Transform();
	Transform(Vector3& position, Vector3& scale, Vector3& rotation, Dimensions2& dimensions);

	// Setters
	void setPosition(Vector3& position);
	void setRotation(Vector3& rotation);
	void setScale(Vector3& scale);

	// Getters
	Vector3& getPosition();
	Vector3& getRotation();
	Vector3& getScale();
	Dimensions2& getDimensions();

	// Debugging
	std::string toString();

private:
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
	Dimensions2 dimensions;
};
