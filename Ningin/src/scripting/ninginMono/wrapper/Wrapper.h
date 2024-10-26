#pragma once

#include "../../../math/Dimensions3.h"
#include "../../../math/Dimensions2.h"
#include "../../../math/vector2.h"
#include "../../../math/Vector3.h"
#include "../../../math/Range.h"
#include "../../../math/Math.h"
#include "../../../sceneSystem/components/colliders/PointCollider.h"
#include "../../../physicsEngine/Mask2.h"
#include "../../../physicsEngine/Mask3.h"
#include "../../../sceneSystem/components/Transform.h"
#include "../../../resourceManager/color/Color.h"
#include "../../../utils/Debug.h"
#include "../../ScriptingEngine.h"
#include "../../../audio/StaticAudioPlayer.h"
#include "../../../environment.h"
#include <mono/jit/jit.h>

using namespace Ningin::Physics;
using namespace Ningin::Components;
using namespace Ningin;

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

#pragma region Dimensions2
    void MonoDimensions2ToString(Dimensions2& dimensions, MonoString** out);
#pragma endregion

#pragma region Dimensions3
    void MonoDimensions3ToString(Dimensions3& dimensions, MonoString** out);
#pragma endregion

#pragma region Range
    void MonoRangeToString(Range& range, MonoString** out);
#pragma endregion

#pragma region Mask2
    void MonoMask2ToString(Mask2& mask, MonoString** out);
#pragma endregion

#pragma region Mask3
    void MonoMask3ToString(Mask3& mask, MonoString** out);
#pragma endregion

#pragma region Point
	void MonoPointToString(PointCollider& point, MonoString** out);
#pragma endregion

#pragma region Transform
	void MonoTransformToString(Transform& transform, MonoString** out);
#pragma endregion

#pragma region Color
	void MonoColorToString(Color& color, MonoString** out);
#pragma endregion

#pragma region StaticAudioPlayer
	void StaticAudioPlayerPlayAudio(MonoString* path);
#pragma endregion

#pragma region Environment
	void EnvironmentGetGameDirectory(MonoString** out);
#pragma endregion