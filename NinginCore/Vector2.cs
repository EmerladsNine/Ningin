using System.Runtime.CompilerServices;
namespace Ningin{
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

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _Abs(ref Vector2 self, out Vector2 result);
        public Vector2 Abs() { _Abs(ref this, out Vector2 result); return result; }
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _sqrt(ref Vector2 self, out Vector2 result);
        public Vector2 Sqrt() { _sqrt(ref this, out Vector2 result); return result; }
           
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _add(ref Vector2 self,ref Vector2 other, out Vector2 result);
        public Vector2 Add(Vector2 Other) { _add(ref this,ref Other, out Vector2 result); return result; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _distance(ref Vector2 self,ref Vector2 other);
        public float Distance(Vector2 Other) => _distance(ref this,ref Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _distanceSquared(ref Vector2 self,ref Vector2 other);
        public float DistanceSquared(Vector2 Other) => _distanceSquared(ref this,ref Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _dot(ref Vector2 self,ref Vector2 other);
        public float Dot(Vector2 Other) => _dot(ref this,ref Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _magnitude(ref Vector2 self);
        public float Magnitude() => _magnitude(ref this);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _magnitudeSquared(ref Vector2 self);
        public float MagnitudeSquared() => _magnitudeSquared(ref this);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _max(ref Vector2 V1,ref Vector2 V2,out Vector2 result);
        public static Vector2 Max(Vector2 V1,Vector2 V2) { _max(ref V1, ref V2, out Vector2 result); return result; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _min(ref Vector2 V1,ref Vector2 V2,out Vector2 result);
        public static Vector2 Min(Vector2 V1,Vector2 V2) { _min(ref V1, ref V2, out Vector2 result); return result; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _clamp(ref Vector2 to_clamp,ref Vector2 min,ref Vector2 max,out Vector2 result);
        public static Vector2 Clamp(Vector2 to_clamp,Vector2 min,Vector2 max) { _clamp(ref to_clamp,ref min, ref max, out Vector2 result); return result; }

    }

}