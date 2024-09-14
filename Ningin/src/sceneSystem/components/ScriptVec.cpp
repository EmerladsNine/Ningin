#include "ScriptVec.h"

ScriptVec::ScriptVec() {}

ScriptVec::~ScriptVec()
{
	for (auto& script : scripts)
	{
		delete script;
	}
}
