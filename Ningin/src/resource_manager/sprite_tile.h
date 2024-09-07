#pragma once

#include <string>
#include "../math/dimensions2.h"
#include "../math/vector2.h"

class SpriteTile {
public:
	// Constructor
	SpriteTile(const std::string& name, const Vector2& inSheetPosition, const Dimensions2& dimensions);

	// Getters
	std::string getName() const;
	Vector2 getInSheetPosition() const;
	Dimensions2 getDimensions() const;

	// Setters
	void setName(const std::string& name);
	void setInSheetPosition(const Vector2& inSheetPosition);
	Vector2 getInSheetPosition(const Vector2& inSheetPosition);
	void setDimensions(const Dimensions2& dimensions);
	Dimensions2 getDimensions(const Dimensions2& dimensions);

private:
	std::string name;
	Vector2 in_sheet_position;
	Dimensions2 dimensions;
};
