#pragma once

#include "force.h"

struct Body {
	float mass;
	float density;
	float bounciness;

	bool is_static;

	Force gravity;
};
