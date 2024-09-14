#pragma once

#include "../math/Dimensions2.h"
#include "../math/Vector2.h"
#include <string>

using namespace std;

class SpriteTile
{
	public:
		SpriteTile(string name, Vector2 inSheetPosition, Dimensions2 dimensions);

		Vector2 GetInSheetPosition();
		Dimensions2 GetDimensions();
		string GetName();

		void SetInSheetPosition(Vector2& inSheetPosition);
		void SetDimensions(Dimensions2& dimensions);
		void SetName(string& name);

	private:
		Vector2 _inSheetPosition;
		Dimensions2 _dimensions;
		string _name;
};
