#include "Wrapper.h"

using namespace Ningin;
using namespace Ningin::Physics;

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
		string text;
		Vector2ToString(vec, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Vector3
	void MonoVector3ToString(Vector3& vec, MonoString** out)
	{
		string text;
		Vector3ToString(vec, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Dimensions2
	void MonoDimensions2ToString(Dimensions2& dimensions, MonoString** out)
	{
		string text;
		Dimensions2ToString(dimensions, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Dimensions3
	void MonoDimensions3ToString(Dimensions3& dimensions, MonoString** out)
	{
		string text;
		Dimensions3ToString(dimensions, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Range
	void MonoRangeToString(Range& range, MonoString** out)
	{
		string text;
		RangeToString(range, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Mask2
	void MonoMask2ToString(Mask2& mask, MonoString** out)
	{
		string text;
		Mask2ToString(mask, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Mask3
	void MonoMask3ToString(Mask3& mask, MonoString** out)
	{
		string text;
		Mask3ToString(mask, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Point
	void MonoPointToString(PointCollider& point, MonoString** out)
	{
		string text;
		PointToString(point, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Transform
	void MonoTransformToString(Transform& transform, MonoString** out)
	{
		string text;
		TransformToString(transform, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region Color
	void MonoColorToString(Color& color, MonoString** out)
	{
		string text;
		ColorToString(color, text);
		*out = ScriptingEngine::mono.GetMonoString(text.c_str());
	}
#pragma endregion

#pragma region StaticAudioPlayer
	void StaticAudioPlayerPlayAudio(MonoString* path)
	{
		char* pathCstr = mono_string_to_utf8(path);
		StaticAudioPlayer::PlayAudio(pathCstr);
	}
#pragma endregion

#pragma region Environment
	void EnvironmentGetGameDirectory(MonoString** out)
	{
		std::filesystem::path path = Environment::GetGameDirectory();
		*out = ScriptingEngine::mono.GetMonoString(path.string().c_str());
	}
#pragma endregion