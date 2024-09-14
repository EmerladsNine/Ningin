#pragma once

#include "../../scripting/Scriptable.h"
#include <vector>

using namespace std;

class ScriptVec
{
	public:
		ScriptVec();
		~ScriptVec();

		vector<Scriptable*> scripts;
};
