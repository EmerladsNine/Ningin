using System.Runtime.CompilerServices;
namespace NinginCore
{
    public struct Vector3
    {
        public static Vector3 UNIT_X = new Vector3(1.0f, 0.0f, 0.0f);
        public static Vector3 UNIT_Y = new Vector3(0.0f, 1.0f, 0.0f);
        public static Vector3 UNIT_Z = new Vector3(0.0f, 0.0f, 1.0f);
        public static Vector3 ZERO = new Vector3(0.0f, 0.0f, 0.0f);
        public static Vector3 ONE = new Vector3(1.0f, 1.0f, 1.0f);

        public float x;
        public float y;
        public float z;

        public Vector3(float x, float y,float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public Vector3 Abs() { InternalCalls.Vector3Abs(ref this, out Vector3 result); return result; }
        public Vector3 Sqrt() { InternalCalls.Vector3SquareRoot(ref this, out Vector3 result); return result; }
        public Vector3 Add(Vector3 Other) { InternalCalls.Vector3Add(ref this,ref Other, out Vector3 result); return result; }
        public float Distance(Vector3 Other) => InternalCalls.Vector3Distance(ref this,ref Other);
        public float DistanceSquared(Vector3 Other) => InternalCalls.Vector3DistanceSquared(ref this,ref Other);
        public float Dot(Vector3 Other) => InternalCalls.Vector3Dot(ref this,ref Other);
        public float Magnitude() => InternalCalls.Vector3Magnitude(ref this);
        public float MagnitudeSquared() => InternalCalls.Vector3MagnitudeSquared(ref this);
        public static Vector3 Max(Vector3 V1,Vector3 V2) { InternalCalls.Vector3Max(ref V1, ref V2, out Vector3 result); return result; }
        public static Vector3 Min(Vector3 V1,Vector3 V2) { InternalCalls.Vector3Min(ref V1, ref V2, out Vector3 result); return result; }
        public static Vector3 Clamp(Vector3 to_clamp,Vector3 min,Vector3 max) { InternalCalls.Vector3Clamp(ref to_clamp,ref min, ref max, out Vector3 result); return result; }
    }
}