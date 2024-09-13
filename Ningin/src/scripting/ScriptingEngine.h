#pragma once

#include "ninginMono/MonoPaths.h"
#include "ninginMono/mono.h"
#include "ScriptLanguage.h"
#include <optional>
#include <string>

class ScriptingEngine
{
	public:
		static Mono mono;

		static void Init(std::optional<MonoPaths> monoPath);

		static Scriptable* GetScript(std::string scriptName , ScriptLanguage language);
};
