#pragma once

#include "ninginMono/MonoPaths.h"
#include "ninginMono/mono.h"
#include "ScriptLanguage.h"
#include <optional>
#include <string>

using namespace std;

class ScriptingEngine
{
	public:
		static Mono mono;

		static void Init(optional<MonoPaths> monoPath,bool debugMode);

		static Scriptable* GetScript(string scriptName, ScriptLanguage language);
};
