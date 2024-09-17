namespace NinginCore
{
    public struct Range
    {
        public float min, max;

        public Range(float min = 0.0f, float max = 10.0f)
        {
            this.min = min;
            this.max = max;
        }

        public float BoundValue(float value)
        {
            return InternalCalls.RangeBoundValue(ref this, value);
        }

        public static float BoundValue(Range range, float value)
        {
            return InternalCalls.RangeBoundValue(ref range, value);
        }
    }
}
