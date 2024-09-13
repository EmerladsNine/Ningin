namespace NinginCore
{
    public struct Vector2
    {
        public static Vector2 UNIT_X = new Vector2(1.0f, 0.0f);
        public static Vector2 UNIT_Y = new Vector2(0.0f, 1.0f);
        public static Vector2 ZERO = new Vector2(0.0f, 0.0f);
        public static Vector2 ONE = new Vector2(1.0f, 1.0f);

        public float x;
        public float y;

        public Vector2(float x = 0.0f, float y = 0.0f)
        {
            this.x = x;
            this.y = y;
        }

        public void Abs()
        {
            InternalCalls.Vector2Abs(ref this, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }

        public void Negate()
        {
            InternalCalls.Vector2Negate(ref this, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }
        public void Scale(float scaler)
        {
            InternalCalls.Vector2Multiply(ref this, scaler, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }

        public void Sqrt()
        {
            InternalCalls.Vector2SquareRoot(ref this, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }

        public void Add(Vector2 Other)
        {
            InternalCalls.Vector2Add(ref this, ref Other, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }

        public void Clamp(Vector2 min, Vector2 max)
        {
            InternalCalls.Vector2Clamp(ref this, ref min, ref max, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }

        public void Normalize()
        {
            InternalCalls.Vector2Normalize(ref this, out Vector2 result);
            this.x = result.x;
            this.y = result.y;
        }

        public float Distance(Vector2 Other) => InternalCalls.Vector2Distance(ref this, ref Other);
        public float DistanceSquared(Vector2 Other) => InternalCalls.Vector2DistanceSquared(ref this, ref Other);
        public float Dot(Vector2 Other) => InternalCalls.Vector2Dot(ref this, ref Other);
        public float Magnitude() => InternalCalls.Vector2Magnitude(ref this);
        public float MagnitudeSquared() => InternalCalls.Vector2MagnitudeSquared(ref this);

        public static float Distance(Vector2 v1, Vector2 v2) => InternalCalls.Vector2Distance(ref v1, ref v2);
        public static float DistanceSquared(Vector2 v1, Vector2 v2) => InternalCalls.Vector2DistanceSquared(ref v1, ref v2);
        public static float Dot(Vector2 v1, Vector2 v2) => InternalCalls.Vector2Dot(ref v1, ref v2);
        public static float Magnitude(Vector2 vec) => InternalCalls.Vector2Magnitude(ref vec);
        public static float MagnitudeSquared(Vector2 vec) => InternalCalls.Vector2MagnitudeSquared(ref vec);
        public static Vector2 Max(Vector2 V1, Vector2 V2) { InternalCalls.Vector2Max(ref V1, ref V2, out Vector2 result); return result; }
        public static Vector2 Min(Vector2 V1, Vector2 V2) { InternalCalls.Vector2Min(ref V1, ref V2, out Vector2 result); return result; }
        public static Vector2 Clamp(Vector2 to_clamp, Vector2 min, Vector2 max) { InternalCalls.Vector2Clamp(ref to_clamp, ref min, ref max, out Vector2 result); return result; }
        public static Vector2 Normalize(Vector2 vec) { InternalCalls.Vector2Normalize(ref vec, out Vector2 result); return result; }

        // Operators
        public static Vector2 operator -(Vector2 vec)
        {
            InternalCalls.Vector2Negate(ref vec, out Vector2 result);
            return result;
        }

        public static Vector2 operator +(Vector2 v1, Vector2 v2)
        {
            InternalCalls.Vector2Add(ref v1, ref v2, out Vector2 result);
            return result;
        }

        public static Vector2 operator -(Vector2 v1, Vector2 v2)
        {
            InternalCalls.Vector2Subtract(ref v1, ref v2, out Vector2 result);
            return result;
        }

        public static Vector2 operator *(Vector2 v1, float a)
        {
            InternalCalls.Vector2Multiply(ref v1, a, out Vector2 result);
            return result;
        }

        public static Vector2 operator *(float a, Vector2 v1)
        {
            InternalCalls.Vector2Multiply(ref v1, a, out Vector2 result);
            return result;
        }

        public static Vector2 operator *(Vector2 v1, Vector2 v2)
        {
            InternalCalls.Vector2Multiply(ref v1, ref v2, out Vector2 result);
            return result;
        }

        public static Vector2 operator /(Vector2 v1, Vector2 v2)
        {
            InternalCalls.Vector2Divide(ref v1, ref v2, out Vector2 result);
            return result;
        }

        public static Vector2 operator /(Vector2 vec, float a)
        {
            InternalCalls.Vector2Divide(ref vec, a, out Vector2 result);
            return result;
        }

        public static Vector2 operator /(float a, Vector2 vec)
        {
            Vector2 _vec = new Vector2(1 / vec.x, 1 / vec.y);
            InternalCalls.Vector2Divide(ref vec, 1 / a, out Vector2 result);
            return result;
        }

        public static bool operator ==(Vector2 v1, Vector2 v2) => InternalCalls.Vector2Equals(ref v1, ref v2);
        public static bool operator !=(Vector2 v1, Vector2 v2) => InternalCalls.Vector2NotEqual(ref v1, ref v2);
        public static bool operator <(Vector2 v1, Vector2 v2) => InternalCalls.Vector2L(ref v1, ref v2);
        public static bool operator <=(Vector2 v1, Vector2 v2) => InternalCalls.Vector2LE(ref v1, ref v2);
        public static bool operator >(Vector2 v1, Vector2 v2) => InternalCalls.Vector2G(ref v1, ref v2);
        public static bool operator >=(Vector2 v1, Vector2 v2) => InternalCalls.Vector2GE(ref v1, ref v2);

        public static Vector2 FromVector3(Vector3 vec)
        {
            InternalCalls.Vector2FromVector3(ref vec, out Vector2 result);
            return result;
        }

        public override bool Equals(object obj)
        {
            if (obj is Vector2)
            {
                return this == (Vector2)obj;
            }

            return false;
        }

        public override int GetHashCode() => new { x, y }.GetHashCode();
    }
}
