using System.Drawing;
using System.Runtime.CompilerServices;
using static System.Net.Mime.MediaTypeNames;

namespace NinginCore
{
    internal class InternalCalls
    {
        #region Vector2
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Abs(ref Vector2 self, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Inverse(ref Vector2 self, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector2Distance(ref Vector2 self, ref Vector2 other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector2DistanceSquared(ref Vector2 self, ref Vector2 other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector2Dot(ref Vector2 self, ref Vector2 other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector2Magnitude(ref Vector2 self);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector2MagnitudeSquared(ref Vector2 self);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Max(ref Vector2 V1, ref Vector2 V2, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Min(ref Vector2 V1, ref Vector2 V2, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2SquareRoot(ref Vector2 self, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Normalize(ref Vector2 self, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2FromVector3(ref Vector3 self, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Clamp(ref Vector2 to_clamp, ref Vector2 min, ref Vector2 max,
            out Vector2 result);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void MonoVector2ToString(ref Vector2 vec, out string str);

        // Operators
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Add(ref Vector2 self, ref Vector2 other, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Negate(ref Vector2 vec, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Subtract(ref Vector2 v1, ref Vector2 v2, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2MultiplyByFloat(ref Vector2 vec, float a, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Multiply(ref Vector2 v1, ref Vector2 v2, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2Divide(ref Vector2 v1, ref Vector2 v2, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector2DivideByFloat(ref Vector2 vec, float a, out Vector2 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector2Equals(ref Vector2 v1, ref Vector2 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector2NotEqual(ref Vector2 v1, ref Vector2 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector2L(ref Vector2 v1, ref Vector2 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector2LE(ref Vector2 v1, ref Vector2 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector2G(ref Vector2 v1, ref Vector2 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector2GE(ref Vector2 v1, ref Vector2 v2);
        #endregion

        #region Vector3
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Abs(ref Vector3 self, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Inverse(ref Vector3 self, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector3Distance(ref Vector3 self, ref Vector3 other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector3DistanceSquared(ref Vector3 self, ref Vector3 other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector3Dot(ref Vector3 self, ref Vector3 other);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector3Magnitude(ref Vector3 self);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Vector3MagnitudeSquared(ref Vector3 self);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Max(ref Vector3 V1, ref Vector3 V2, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Min(ref Vector3 V1, ref Vector3 V2, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3SquareRoot(ref Vector3 self, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3FromVector2(ref Vector2 self, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Normalize(ref Vector3 self, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Clamp(ref Vector3 to_clamp, ref Vector3 min, ref Vector3 max,
            out Vector3 result);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void MonoVector3ToString(ref Vector3 vec, out string str);

        // Operators
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Add(ref Vector3 self, ref Vector3 other, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Negate(ref Vector3 vec, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Subtract(ref Vector3 v1, ref Vector3 v2, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3MultiplyByFloat(ref Vector3 vec, float a, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Multiply(ref Vector3 v1, ref Vector3 v2, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3Divide(ref Vector3 v1, ref Vector3 v2, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Vector3DivideByFloat(ref Vector3 vec, float a, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector3Equals(ref Vector3 v1, ref Vector3 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector3NotEqual(ref Vector3 v1, ref Vector3 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector3L(ref Vector3 v1, ref Vector3 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector3LE(ref Vector3 v1, ref Vector3 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector3G(ref Vector3 v1, ref Vector3 v2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Vector3GE(ref Vector3 v1, ref Vector3 v2);
        #endregion

        #region Math
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Clamp(float val_to_clamp, float min, float max);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float DegreesToRadians(float deg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern double Radical(double number, int n);
        #endregion

        #region Dimensions2
        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Dimensions2ToString();
        #endregion

        #region Dimensions3
        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Dimensions3ToString();
        #endregion

        #region Debug
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void DebugLogInfo(string message);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void DebugLogWarning(string message);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void DebugLogError(string message);
        #endregion

        #region Point
        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void PointToString();

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void PointFromVector2(ref Vector2 self, out Point result);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void PointFromVector3(ref Vector3 self, out Point result);
        #endregion

        #region Mask2

        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mask2ToString();
        #endregion

        #region Mask3

        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mask3ToString();
        #endregion

        #region Range
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float RangeBoundValue(ref Range<float> range, float val);

        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void RangeToString();
        #endregion

        #region Transform
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformSetPosition(ref Transform transform, ref Vector3 position);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformSetRotation(ref Transform transform, ref Vector3 rotation);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformSetScale(ref Transform transform, ref Vector3 scale);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformGetPosition(ref Transform transform, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformGetRotation(ref Transform transform, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformGetScale(ref Transform transform, out Vector3 result);

        // Todo To String
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformToString();
        #endregion

        #region TextRenderer
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextSetTextColor(ref TextRenderer textRenderer, ref Color color);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextSetText(ref TextRenderer textRenderer, ref string text);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextSetFontSize(ref TextRenderer textRenderer, uint fontSize);
        #endregion

        #region SpriteRenderer
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteSetTintingColor(ref SpriteRenderer spriteRenderer, ref Color color);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteSetUseTint(ref SpriteRenderer spriteRenderer, bool useTint);
        #endregion

        #region Color
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ColorFromRGB(uint rgb, out Color result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ColorFromRGBA(uint r, uint g, uint b, uint a, out Color result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ColorFromColor(ref Color color, uint a, out Color result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ColorSetAlpha(ref Color color, uint a);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ColorToString(ref Color color, out string result);
        #endregion
    }
}
