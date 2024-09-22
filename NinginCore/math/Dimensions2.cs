namespace NinginCore
{
    public struct Dimensions2
    {
        public uint width, height;

        public Dimensions2(uint width = 0, uint height = 0)
        {
            this.width = width;
            this.height = height;
        }

        public override string ToString()
        {
            InternalCalls.MonoDimensions2ToString(ref this, out string result);
            return result;
        }
    }
}
