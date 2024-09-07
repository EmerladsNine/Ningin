#pragma once

#include "../math/dimensions2.h"

/**
 * @brief A struct representing a character in a font.
 *
 * Fields:
 * - ascii_index: The ASCII index of the character. This indicates the position of the character
 *   in the ASCII table.
 * - size: The size of the glyph (character) in pixels.
 * - bearing: The offset from the baseline to the top-left corner of the glyph.
 * - advance: The horizontal offset to advance to the next character, in pixels.
 */
class Character {
public:
	// Constructors
	Character(int ascii_index, const Dimensions2& size, const Dimensions2& bearing, unsigned int advance);
	Character() = default;

	// Accessors
	int getAsciiIndex() const;
	const Dimensions2& getSize() const;
	const Dimensions2& getBearing() const;
	unsigned int getAdvance() const;

private:
	int ascii_index;
	Dimensions2 size;
	Dimensions2 bearing;
	unsigned int advance;
};
