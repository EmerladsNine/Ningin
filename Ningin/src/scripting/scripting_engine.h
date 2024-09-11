#pragma once
#include "ningin_mono/mono.h"
#include "ningin_mono/mono_paths.h"
#include "script_language.h"
#include <optional>
#include <string>

class ScriptingEngine
{
public:
	static Mono mono;
	static void Init(std::optional<MonoPaths> monoPath);
	static void GetScript(std::string scriptName , ScriptLanguage language);
};