#include "ScriptingEngine.h"

Mono ScriptingEngine::mono;

void ScriptingEngine::Init(optional<MonoPaths> monoPath)
{
	if (monoPath.has_value())
	{
		mono.Init(monoPath.value().monoPath, monoPath.value().gameAssemblyFileName);
	}
}

Scriptable* ScriptingEngine::GetScript(string scriptName, ScriptLanguage language)
{
	switch (language)
	{
		case CSHARP:
			return mono.GetScript(scriptName);
			break;

		case PYTHON:
			break;

		case NS:
			break;

		default:
			break;
	}
	return nullptr;
}
