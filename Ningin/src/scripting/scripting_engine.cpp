#include "scripting_engine.h"
Mono ScriptingEngine::mono;

void ScriptingEngine::Init(std::optional<MonoPaths> monoPath)
{
	if (monoPath.has_value())
	{
		mono.Init(monoPath.value().monoPath, monoPath.value().gameAssemblyFileName);
	}
}

void ScriptingEngine::GetScript(std::string scriptName, ScriptLanguage language)
{
	switch (language)
	{
	case CSHARP:
		mono.GetScript(scriptName);
		break;
	case PYTHON:
		break;
	case NS:
		break;
	default:
		break;
	}
}
