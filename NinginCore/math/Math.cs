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
        public static double Clamp(double val_to_clamp, double min, double max)
            => InternalCalls.Clamp(val_to_clamp, min, max);
        public static int Clamp(int val_to_clamp, int min, int max)
            => InternalCalls.Clamp(val_to_clamp, min, max);
        public static uint Clamp(uint val_to_clamp, uint min, uint max)
            => InternalCalls.Clamp(val_to_clamp, min, max);
    }
}
