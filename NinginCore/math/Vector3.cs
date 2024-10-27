namespace NinginCore
{
    public struct Vector3
    {
        public static Vector3 UNIT_X = new Vector3(1.0f, 0.0f, 0.0f);
        public static Vector3 UNIT_Y = new Vector3(0.0f, 1.0f, 0.0f);
        public static Vector3 UNIT_Z = new Vector3(0.0f, 0.0f, 1.0f);
        public static Vector3 ZERO = new Vector3(0.0f, 0.0f, 0.0f);
        public static Vector3 ONE = new Vector3(1.0f, 1.0f, 1.0f);

        public float x, y, z;

        public Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public Vector3 Abs()
        {
            InternalCalls.Vector3Abs(ref this, out Vector3 result);
            return result;
        }

        public Vector3 Negate()
        {
            InternalCalls.Vector3Negate(ref this, out Vector3 result);
            return result;
        }
        public Vector3 Scale(float scaler)
        {
            InternalCalls.Vector3MultiplyByFloat(ref this, scaler, out Vector3 result);
            return result;
        }

        public Vector3 Sqrt()
        {
            InternalCalls.Vector3SquareRoot(ref this, out Vector3 result);
            return result;
        }

        public Vector3 Add(Vector3 Other)
        {
            InternalCalls.Vector3Add(ref this, ref Other, out Vector3 result);
            return result;
        }

        public Vector3 Clamp(Vector3 min, Vector3 max)
        {
            InternalCalls.Vector3Clamp(ref this, ref min, ref max, out Vector3 result);
            return result;
        }

        public Vector3 Normalize()
        {
            InternalCalls.Vector3Normalize(ref this, out Vector3 result);
            return result;
        }
        public Vector3 Inverse()
        {
            InternalCalls.Vector3Inverse(ref this, out Vector3 result);
            return result;
        }

        public Vector3 CrossProduct(Vector3 rightVector)
        {
            InternalCalls.Vector3Cross(ref this, ref rightVector, out Vector3 result);
            return result;
        }

        public float Distance(Vector3 Other) => InternalCalls.Vector3Distance(ref this, ref Other);
        public float Dot(Vector3 Other) => InternalCalls.Vector3Dot(ref this, ref Other);
        public float Magnitude() => InternalCalls.Vector3Magnitude(ref this);
        public float MagnitudeSquared() => InternalCalls.Vector3MagnitudeSquared(ref this);
        public float DistanceSquared(Vector3 Other)
            => InternalCalls.Vector3DistanceSquared(ref this, ref Other);
        public override string ToString()
        {
            InternalCalls.MonoVector3ToString(ref this, out string result);
            return result;
        }

        public static float Dot(Vector3 v1, Vector3 v2) => InternalCalls.Vector3Dot(ref v1, ref v2);
        public static float Magnitude(Vector3 vec) => InternalCalls.Vector3Magnitude(ref vec);
        public static float MagnitudeSquared(Vector3 vec) => InternalCalls.Vector3MagnitudeSquared(ref vec);

        public static float Distance(Vector3 v1, Vector3 v2)
            => InternalCalls.Vector3Distance(ref v1, ref v2);

        public static float DistanceSquared(Vector3 v1, Vector3 v2)
            => InternalCalls.Vector3DistanceSquared(ref v1, ref v2);

        public static Vector3 Max(Vector3 V1, Vector3 V2)
        {
            InternalCalls.Vector3Max(ref V1, ref V2, out Vector3 result);
            return result;
        }

        public static Vector3 Min(Vector3 V1, Vector3 V2)
        {
            InternalCalls.Vector3Min(ref V1, ref V2, out Vector3 result);
            return result;
        }

        public static Vector3 Clamp(Vector3 to_clamp, Vector3 min, Vector3 max)
        {
            InternalCalls.Vector3Clamp(ref to_clamp, ref min, ref max, out Vector3 result);
            return result;
        }

        public static Vector3 Normalize(Vector3 vec)
        {
            InternalCalls.Vector3Normalize(ref vec, out Vector3 result);
            return result;
        }

        public static Vector3 Inverse(Vector3 vec)
        {
            InternalCalls.Vector3Inverse(ref vec, out Vector3 result);
            return result;
        }

        // Operators
        public static Vector3 operator -(Vector3 vec)
        {
            InternalCalls.Vector3Negate(ref vec, out Vector3 result);
            return result;
        }

        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {
            InternalCalls.Vector3Add(ref v1, ref v2, out Vector3 result);
            return result;
        }

        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {
            InternalCalls.Vector3Subtract(ref v1, ref v2, out Vector3 result);
            return result;
        }

        public static Vector3 operator *(Vector3 v1, float a)
        {
            InternalCalls.Vector3MultiplyByFloat(ref v1, a, out Vector3 result);
            return result;
        }

        public static Vector3 operator *(float a, Vector3 v1)
        {
            InternalCalls.Vector3MultiplyByFloat(ref v1, a, out Vector3 result);
            return result;
        }

        public static Vector3 operator *(Vector3 v1, Vector3 v2)
        {
            InternalCalls.Vector3Multiply(ref v1, ref v2, out Vector3 result);
            return result;
        }

        public static Vector3 operator /(Vector3 v1, Vector3 v2)
        {
            InternalCalls.Vector3Divide(ref v1, ref v2, out Vector3 result);
            return result;
        }

        public static Vector3 operator /(Vector3 vec, float a)
        {
            InternalCalls.Vector3DivideByFloat(ref vec, a, out Vector3 result);
            return result;
        }

        public static Vector3 operator /(float a, Vector3 vec)
        {
            InternalCalls.Vector3Inverse(ref vec, out Vector3 inversedVec);
            InternalCalls.Vector3DivideByFloat(ref inversedVec, 1 / a, out Vector3 result);
            return result;
        }

        public static bool operator <(Vector3 v1, Vector3 v2) => InternalCalls.Vector3L(ref v1, ref v2);
        public static bool operator <=(Vector3 v1, Vector3 v2) => InternalCalls.Vector3LE(ref v1, ref v2);
        public static bool operator >(Vector3 v1, Vector3 v2) => InternalCalls.Vector3G(ref v1, ref v2);
        public static bool operator >=(Vector3 v1, Vector3 v2) => InternalCalls.Vector3GE(ref v1, ref v2);

        public static bool operator ==(Vector3 v1, Vector3 v2)
            => InternalCalls.Vector3Equals(ref v1, ref v2);

        public static bool operator !=(Vector3 v1, Vector3 v2)
            => InternalCalls.Vector3NotEqual(ref v1, ref v2);

        public static Vector3 FromVector3(Vector2 vec)
        {
            InternalCalls.Vector3FromVector2(ref vec, out Vector3 result);
            return result;
        }

        public override bool Equals(object obj)
        {
            if (obj is Vector3 vector)
            {
                return this == vector;
            }

            return false;
        }

        public override int GetHashCode() => new { x, y, z }.GetHashCode();
    }
}
