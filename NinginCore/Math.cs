namespace NinginCore
{
    public static class Math
    {

        public const double PI = System.Math.PI;
        public const double TOL = 1e-6;

        public static float DegreesToRadians(float deg) => InternalCalls.DegreesToRadians(deg);
        public static double Clamp(double val_to_clamp, double min, double max) => InternalCalls.Clamp(val_to_clamp, min, max);
        public static double Radical(double number, int n) => InternalCalls.Radical(number, n);
    }
}
