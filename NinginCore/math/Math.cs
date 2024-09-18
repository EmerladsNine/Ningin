namespace NinginCore
{
    public static class Math
    {

        public const double PI = System.Math.PI;
        public const double TOL = 1e-6;

        public static float DegreesToRadians(float deg) => InternalCalls.DegreesToRadians(deg);
        public static double Radical(double number, int n) => InternalCalls.Radical(number, n);
        public static float Clamp(float val_to_clamp, float min, float max)
            => InternalCalls.Clamp(val_to_clamp, min, max);
    }
}
