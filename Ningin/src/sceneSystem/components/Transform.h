#pragma once

#include "../../math/Dimensions2.h"
#include "../../math/Vector3.h"
#include <format>

using namespace std;

class Transform
{
	public:
		Transform(Vector3& position, Vector3& scale, Vector3& rotation, Dimensions2& dimensions);
		Transform();

		void SetPosition(Vector3& position);
		void SetRotation(Vector3& rotation);
		void SetScale(Vector3& scale);

		Vector3& GetPosition();
		Vector3& GetRotation();
		Vector3& GetScale();
		Dimensions2& GetDimensions();

		string ToString();

	private:
		Vector3 _position;
		Vector3 _scale;
		Vector3 _rotation;
		Dimensions2 _dimensions;
};
