namespace NinginCore
{
    public struct Dimensions3
    {
        public uint width, height, depth;

        public Dimensions3(uint width = 0, uint height = 0, uint depth = 0)
        {
            this.width = width;
            this.height = height;
            this.depth = depth;
        }

        public override string ToString()
        {
            InternalCalls.MonoDimensions3ToString(ref this, out string result);
            return result;
        }
    }
}
