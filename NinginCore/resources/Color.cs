namespace NinginCore
{
    public struct Color
    {
        private uint _r;
        private uint _g;
        private uint _b;
        private uint _a;

        public uint r { get { return _r; } private set {} }
        public uint g { get { return _g; } private set {} }
        public uint b { get { return _b; } private set {} }

        public uint a
        { 
            get { return _a; }

            set
            {
                _a = value;
                InternalCalls.ColorSetAlpha(ref this, value);
            } 
        }

        public Color(uint r, uint g, uint b, uint a)
        {
            this._r = r;
            this._g = g;
            this._b = b;
            this._a = a;
        }

        public static Color FromRGB(uint rgb)
        {
            InternalCalls.ColorFromRGB(rgb, out Color result);
            return result;
        }

        public static Color FromRGBA(uint r, uint g, uint b, uint a)
        {
            InternalCalls.ColorFromRGBA(r, g, b, a, out Color result);
            return result;
        }

        public static Color FromColor(Color color, uint a)
        {
            InternalCalls.ColorFromColor(ref color, a, out Color result);
            return result;
        }
    }
}
