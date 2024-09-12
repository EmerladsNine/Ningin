#pragma once

#include "../math/Dimensions2.h"
#include "../math/Vector2.h"
#include <string>

class SpriteTile
{
	public:
		SpriteTile(std::string& name, Vector2& inSheetPosition, Dimensions2& dimensions);

		Vector2 GetInSheetPosition();
		Dimensions2 GetDimensions();
		std::string GetName();

		void SetInSheetPosition(Vector2& inSheetPosition);
		void SetDimensions(Dimensions2& dimensions);
		void SetName(std::string& name);

	private:
		Vector2 inSheetPosition;
		Dimensions2 dimensions;
		std::string name;
};
