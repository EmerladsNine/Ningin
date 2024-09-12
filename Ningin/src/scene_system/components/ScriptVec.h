#pragma once
#include <vector>
#include "../../scripting/scriptable.h"
class ScriptVec
{
public:
	std::vector<Scriptable*> scripts;
	ScriptVec();
	~ScriptVec();
};

