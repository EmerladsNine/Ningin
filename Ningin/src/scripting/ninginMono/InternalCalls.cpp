#include "InternalCalls.h"
#include "../../math/Dimensions3.h"
#include "../../math/Dimensions2.h"
#include "../../math/Vector2.h"
#include "../../math/Vector3.h"
#include "../../math/Range.h"
#include "../../math/Math.h"
#include "../../physicsManager/colliders/Point.h"
#include "../../physicsManager/Mask2.h"
#include "../../physicsManager/Mask3.h"
#include "wrapper/Wrapper.h"
#include "../../sceneSystem/components/Transform.h"
#include "../../sceneSystem/components/SpriteRenderer.h"
#include "../../sceneSystem/components/TextRenderer.h"
#include "../../resourceManager/color/Color.h"
#include "../../sceneSystem/entity/Entity.h"

void AddInternalCalls()
{
    #pragma region Entity
        AddInternalCall(EntitySetTransform);
        AddInternalCall(EntityHasComponent);
        AddInternalCall(EntityGetComponent);
    #pragma endregion

    #pragma region Vector2
        AddInternalCall(Vector2Abs);
        AddInternalCall(Vector2Clamp);
        AddInternalCall(Vector2Distance);
        AddInternalCall(Vector2DistanceSquared);
        AddInternalCall(Vector2Dot);
        AddInternalCall(Vector2Magnitude);
        AddInternalCall(Vector2MagnitudeSquared);
        AddInternalCall(Vector2Normalize);
        AddInternalCall(Vector2Max);
        AddInternalCall(Vector2Min);
        AddInternalCall(Vector2SquareRoot);
        AddInternalCall(Vector2Inverse);
        AddInternalCall(MonoVector2ToString);
        AddInternalCall(Vector2FromVector3);
        AddInternalCall(Vector2Add);
        AddInternalCall(Vector2Negate);
        AddInternalCall(Vector2Subtract);
        AddInternalCall(Vector2MultiplyByFloat);
        AddInternalCall(Vector2Multiply);
        AddInternalCall(Vector2Divide);
        AddInternalCall(Vector2DivideByFloat);
        AddInternalCall(Vector2Equals);
        AddInternalCall(Vector2NotEqual);
        AddInternalCall(Vector2L);
        AddInternalCall(Vector2LE);
        AddInternalCall(Vector2G);
        AddInternalCall(Vector2GE);
    #pragma endregion

    #pragma region Vector3
        AddInternalCall(Vector3Abs);
        AddInternalCall(Vector3Clamp);
        AddInternalCall(Vector3Distance);
        AddInternalCall(Vector3DistanceSquared);
        AddInternalCall(Vector3Inverse);
        AddInternalCall(Vector3Normalize);
        AddInternalCall(Vector3Dot);
        AddInternalCall(Vector3Magnitude);
        AddInternalCall(Vector3MagnitudeSquared);
        AddInternalCall(Vector3Max);
        AddInternalCall(Vector3Min);
        AddInternalCall(Vector3SquareRoot);
        AddInternalCall(MonoVector3ToString);
        AddInternalCall(Vector3FromVector2);
        AddInternalCall(Vector3Add);
        AddInternalCall(Vector3Negate);
        AddInternalCall(Vector3Subtract);
        AddInternalCall(Vector3MultiplyByFloat);
        AddInternalCall(Vector3Multiply);
        AddInternalCall(Vector3Divide);
        AddInternalCall(Vector3DivideByFloat);
        AddInternalCall(Vector3Equals);
        AddInternalCall(Vector3NotEqual);
        AddInternalCall(Vector3L);
        AddInternalCall(Vector3LE);
        AddInternalCall(Vector3G);
        AddInternalCall(Vector3GE);
    #pragma endregion

    #pragma region Math
        AddInternalCall(Clamp);
        AddInternalCall(DegreesToRadians);
        AddInternalCall(Radical);
    #pragma endregion

    #pragma region Dimensions2
        AddInternalCall(MonoDimensions2ToString);
    #pragma endregion

    #pragma region Dimensions3
        AddInternalCall(MonoDimensions3ToString);
    #pragma endregion

    #pragma region Range
        AddInternalCall(MonoRangeToString);
        AddInternalCall(RangeBoundValue);
    #pragma endregion

    #pragma region Mask2
        AddInternalCall(MonoMask2ToString);
    #pragma endregion

    #pragma region Mask3
        AddInternalCall(MonoMask3ToString);
    #pragma endregion

    #pragma region Point
        AddInternalCall(PointFromVector2);
        AddInternalCall(PointFromVector3);
        AddInternalCall(MonoPointToString);
    #pragma endregion

    #pragma region Transform
        AddInternalCall(TransformGetPosition);
        AddInternalCall(TransformSetPosition);
        AddInternalCall(TransformGetRotation);
        AddInternalCall(TransformSetRotation);
        AddInternalCall(TransformGetScale);
        AddInternalCall(TransformSetScale);
        AddInternalCall(MonoTransformToString);
    #pragma endregion

    #pragma region SpriteRenderer
        AddInternalCall(SpriteSetTintingColor);
        AddInternalCall(SpriteSetUseTint);
    #pragma endregion

    #pragma region TextRenderer
        AddInternalCall(TextSetFontSize);
        AddInternalCall(TextSetFont);
        AddInternalCall(TextSetText);
        AddInternalCall(TextSetTextColor);
    #pragma endregion

    #pragma region Color
        AddInternalCall(ColorFromRGB);
        AddInternalCall(ColorFromRGBA);
        AddInternalCall(ColorFromColor);
        AddInternalCall(ColorSetAlpha);
        AddInternalCall(MonoColorToString);
    #pragma endregion

    #pragma region Debug
        AddInternalCall(DebugLogInfo);
        AddInternalCall(DebugLogWarning);
        AddInternalCall(DebugLogError);
    #pragma endregion
}
