#pragma once

#include "../../../utils/Debug.h"
#include "../../../math/vector2.h"
#include "../../../math/vector3.h"
#include "../../ScriptingEngine.h"
#include <mono/jit/jit.h>

#pragma region Debug
	void DebugLogInfo(MonoString* message);

	void DebugLogError(MonoString* message);

	void DebugLogWarning(MonoString* message);
#pragma endregion

#pragma region Vector2
	void MonoVector2ToString(Vector2& vec, MonoString** out);
#pragma endregion

#pragma region Vector3
	void MonoVector3ToString(Vector3& vec, MonoString** out);
#pragma endregion
