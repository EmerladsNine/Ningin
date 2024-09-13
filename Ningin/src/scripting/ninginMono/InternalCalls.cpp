#include "InternalCalls.h"
#include "../../math/vector2.h"
#include "../../math/vector3.h"
#include "../../math/math.h"
#include "../../math/dimensions2.h"
#include "../../math/dimensions3.h"
#include "wrapper/DebugWrapper.h"

void AddInternalCalls() {
    #pragma region Vector2
        AddInternalCall(Vector2Abs);
        AddInternalCall(Vector2Add);
        AddInternalCall(Vector2Clamp);
        AddInternalCall(Vector2Distance);
        AddInternalCall(Vector2DistanceSquared);
        AddInternalCall(Vector2Dot);
        AddInternalCall(Vector2Magnitude);
        AddInternalCall(Vector2MagnitudeSquared);
        AddInternalCall(Vector2Max);
        AddInternalCall(Vector2Min);
        AddInternalCall(Vector2SquareRoot);
        AddInternalCall(Vector2ToString);
    #pragma endregion

    #pragma region Vector3
        AddInternalCall(Vector3Abs);
        AddInternalCall(Vector3Add);
        AddInternalCall(Vector3Clamp);
        AddInternalCall(Vector3Distance);
        AddInternalCall(Vector3DistanceSquared);
        AddInternalCall(Vector3Dot);
        AddInternalCall(Vector3Magnitude);
        AddInternalCall(Vector3MagnitudeSquared);
        AddInternalCall(Vector3Max);
        AddInternalCall(Vector3Min);
        AddInternalCall(Vector3SquareRoot);
        AddInternalCall(Vector3ToString);
    #pragma endregion

    #pragma region Math
        AddInternalCall(Clamp);
        AddInternalCall(DegreesToRadians);
        AddInternalCall(Radical);
    #pragma endregion

    #pragma region Dimensions2
        AddInternalCall(Dimensions2ToString);
    #pragma endregion

    #pragma region Dimensions3
        AddInternalCall(Dimensions3ToString);
    #pragma endregion

    #pragma region Debug
        AddInternalCall(DebugLogInfo);
        AddInternalCall(DebugLogWarning);
        AddInternalCall(DebugLogError);
    #pragma endregion
}
