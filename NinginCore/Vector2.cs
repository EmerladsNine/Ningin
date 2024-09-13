using System.Runtime.CompilerServices;
namespace NinginCore
{
    public struct Vector2 {
        public static Vector2 UNIT_X = new Vector2(1.0f, 0.0f);
        public static Vector2 UNIT_Y = new Vector2(0.0f, 1.0f);
        public static Vector2 ZERO = new Vector2(0.0f, 0.0f);
        public static Vector2 ONE = new Vector2(1.0f, 1.0f);

        public float x;
        public float y;

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public Vector2 Abs() { InternalCalls.Vector2Abs(ref this, out Vector2 result); return result; }
        public Vector2 Sqrt() { InternalCalls.Vector2SquareRoot(ref this, out Vector2 result); return result; }
        public Vector2 Add(Vector2 Other) { InternalCalls.Vector2Add(ref this,ref Other, out Vector2 result); return result; }
        public float Distance(Vector2 Other) => InternalCalls.Vector2Distance(ref this,ref Other);
        public float DistanceSquared(Vector2 Other) => InternalCalls.Vector2DistanceSquared(ref this,ref Other);
        public float Dot(Vector2 Other) => InternalCalls.Vector2Dot(ref this,ref Other);
        public float Magnitude() => InternalCalls.Vector2Magnitude(ref this);
        public float MagnitudeSquared() => InternalCalls.Vector2MagnitudeSquared(ref this);
        public static Vector2 Max(Vector2 V1,Vector2 V2) { InternalCalls.Vector2Max(ref V1, ref V2, out Vector2 result); return result; }
        public static Vector2 Min(Vector2 V1,Vector2 V2) { InternalCalls.Vector2Min(ref V1, ref V2, out Vector2 result); return result; }
        public static Vector2 Clamp(Vector2 to_clamp,Vector2 min,Vector2 max) { InternalCalls.Vector2Clamp(ref to_clamp,ref min, ref max, out Vector2 result); return result; }

    }

}