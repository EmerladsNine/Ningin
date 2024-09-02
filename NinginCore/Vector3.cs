using System.Runtime.CompilerServices;
namespace Ningin
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

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _Abs(ref Vector3 self, out Vector3 result);
        public Vector3 Abs() { _Abs(ref this, out Vector3 result); return result; }
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _sqrt(ref Vector3 self, out Vector3 result);
        public Vector3 Sqrt() { _sqrt(ref this, out Vector3 result); return result; }
           
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _add(ref Vector3 self,ref Vector3 other, out Vector3 result);
        public Vector3 Add(Vector3 Other) { _add(ref this,ref Other, out Vector3 result); return result; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _distance(ref Vector3 self,ref Vector3 other);
        public float Distance(Vector3 Other) => _distance(ref this,ref Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _distanceSquared(ref Vector3 self,ref Vector3 other);
        public float DistanceSquared(Vector3 Other) => _distanceSquared(ref this,ref Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _dot(ref Vector3 self,ref Vector3 other);
        public float Dot(Vector3 Other) => _dot(ref this,ref Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _magnitude(ref Vector3 self);
        public float Magnitude() => _magnitude(ref this);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern float _magnitudeSquared(ref Vector3 self);
        public float MagnitudeSquared() => _magnitudeSquared(ref this);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _max(ref Vector3 V1,ref Vector3 V2,out Vector3 result);
        public static Vector3 Max(Vector3 V1,Vector3 V2) { _max(ref V1, ref V2, out Vector3 result); return result; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _min(ref Vector3 V1,ref Vector3 V2,out Vector3 result);
        public static Vector3 Min(Vector3 V1,Vector3 V2) { _min(ref V1, ref V2, out Vector3 result); return result; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void _clamp(ref Vector3 to_clamp,ref Vector3 min,ref Vector3 max,out Vector3 result);
        public static Vector3 Clamp(Vector3 to_clamp,Vector3 min,Vector3 max) { _clamp(ref to_clamp,ref min, ref max, out Vector3 result); return result; }
    }
}