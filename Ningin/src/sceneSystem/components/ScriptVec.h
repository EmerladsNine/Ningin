#pragma once

#include "../../scripting/Scriptable.h"
#include <vector>

class ScriptVec
{
	public:
		ScriptVec();
		~ScriptVec();

		std::vector<Scriptable*> scripts;
};
