using System;
using System.Runtime.CompilerServices;
namespace Ningin{
    public static class Math{
        
        public const double PI = System.Math.PI;
        public const double TOL = 1e-6;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float DegreesToRadians(float deg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double Clamp(double val_to_clamp,double min,double max);
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double Radical(double number,int n);
    }
}