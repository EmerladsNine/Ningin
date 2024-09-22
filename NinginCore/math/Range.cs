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
            Range<float> range = new Range<float>((float)(object)min, (float)(object)max);
            return (int)InternalCalls.RangeBoundValue(ref range, (float)value);
        }

        private uint BoundValue(uint value)
        {
            Range<float> range = new Range<float>((float)(object)min, (float)(object)max);
            return (uint)InternalCalls.RangeBoundValue(ref range, (float)value);
        }

        private float BoundValue(float value)
        {
            Range<float> range = new Range<float>((float)(object)min, (float)(object)max);
            return InternalCalls.RangeBoundValue(ref range, value);
        }

        private double BoundValue(double value)
        {
            Range<float> range = new Range<float>((float)(object)min, (float)(object)max);
            return (double)InternalCalls.RangeBoundValue(ref range, (float)value);
        }

        public override string ToString()
        {
            Range<float> range = new Range<float>((float)(object)min, (float)(object)max);
            InternalCalls.MonoRangeToString(ref range, out string result);
            return result;
        }
    }
}
