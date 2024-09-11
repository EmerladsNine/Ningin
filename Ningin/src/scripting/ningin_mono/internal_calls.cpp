#include "internal_calls.h"
#include "../../math/vector2.h"
#include "../../math/vector3.h"
#include "../../math/math.h"
#include "../../math/dimensions2.h"
#include "../../math/dimensions3.h"

void AddInternalCalls() {
    #pragma region Vector2
        AddInternalCall(Vector2_abs);
        AddInternalCall(Vector2_add);
        AddInternalCall(Vector2_clamp);
        AddInternalCall(Vector2_distance);
        AddInternalCall(Vector2_distanceSquared);
        AddInternalCall(Vector2_dot);
        AddInternalCall(Vector2_magnitude);
        AddInternalCall(Vector2_magnitudeSquared);
        AddInternalCall(Vector2_max);
        AddInternalCall(Vector2_min);
        AddInternalCall(Vector2_squareRoot);
        AddInternalCall(Vector2_toString);
    #pragma endregion

    #pragma region Vector3
        AddInternalCall(Vector3_abs);
        AddInternalCall(Vector3_add);
        AddInternalCall(Vector3_clamp);
        AddInternalCall(Vector3_distance);
        AddInternalCall(Vector3_distanceSquared);
        AddInternalCall(Vector3_dot);
        AddInternalCall(Vector3_magnitude);
        AddInternalCall(Vector3_magnitudeSquared);
        AddInternalCall(Vector3_max);
        AddInternalCall(Vector3_min);
        AddInternalCall(Vector3_squareRoot);
        AddInternalCall(Vector3_toString);
    #pragma endregion

    #pragma region Math
        AddInternalCall(clamp);
        AddInternalCall(degrees_to_radians);
        AddInternalCall(radical);
    #pragma endregion

    #pragma region Dimensions2
        AddInternalCall(Dimensions2_toString);
    #pragma endregion

    #pragma region Dimensions3
        AddInternalCall(Dimensions3_toString);
    #pragma endregion
}
