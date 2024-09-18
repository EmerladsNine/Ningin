using System;

namespace NinginCore
{
    public struct Range<T> where T : struct, IComparable<T>, IEquatable<T>
    {
        public T min, max;

        public Range(T min, T max)
        {
            this.min = min;
            this.max = max;
        }

        public T BoundValue(T value)
        {
            if (typeof(T) == typeof(int))
                return (T)(object)BoundValue((int)(object)value);
            if (typeof(T) == typeof(uint))
                return (T)(object)BoundValue((uint)(object)value);
            if (typeof(T) == typeof(float))
                return (T)(object)BoundValue((float)(object)value);
            if (typeof(T) == typeof(double))
                return (T)(object)BoundValue((double)(object)value);

            throw new InvalidOperationException("Type not supported.");
        }

        private int BoundValue(int value)
        {
            Range<int> range = new Range<int>((int)(object)min, (int)(object)max);
            return InternalCalls.RangeBoundValue(ref range, value);
        }

        private uint BoundValue(uint value)
        {
            Range<uint> range = new Range<uint>((uint)(object)min, (uint)(object)max);
            return InternalCalls.RangeBoundValue(ref range, value);
        }

        private float BoundValue(float value)
        {
            Range<float> range = new Range<float>((float)(object)min, (float)(object)max);
            return InternalCalls.RangeBoundValue(ref range, value);
        }

        private double BoundValue(double value)
        {
            Range<double> range = new Range<double>((double)(object)min, (double)(object)max);
            return InternalCalls.RangeBoundValue(ref range, value);
        }
    }
}
