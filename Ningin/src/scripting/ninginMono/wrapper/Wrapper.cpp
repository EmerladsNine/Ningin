#include "Wrapper.h"

#pragma region Debug
	void DebugLogInfo(MonoString* message)
	{
		char* messageCstr = mono_string_to_utf8(message);
		LogInfo(messageCstr);
	}

	void DebugLogError(MonoString* message)
	{
		char* messageCstr = mono_string_to_utf8(message);
		LogInfo(messageCstr);
	}

	void DebugLogWarning(MonoString* message)
	{
		char* messageCstr = mono_string_to_utf8(message);
		LogInfo(messageCstr);
	}
#pragma endregion

#pragma region Vector2
	void MonoVector2ToString(Vector2& vec, MonoString** out)
	{
		std:string text;
		Vector2ToString(vec, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Vector3
	void MonoVector3ToString(Vector3& vec, MonoString** out)
	{
		std:string text;
		Vector3ToString(vec, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion