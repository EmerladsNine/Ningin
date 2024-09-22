namespace NinginCore
{
    public struct Point
    {
        public int x, y;

        public Point(int x = 0, int y = 0)
        {
            this.x = x;
            this.y = y;
        }

        public static Point ToPoint(Vector2 vec)
        {
            InternalCalls.PointFromVector2(ref vec, out Point result);
            return result;
        }

        public static Point ToPoint(Vector3 vec)
        {
            InternalCalls.PointFromVector3(ref vec, out Point result);
            return result;
        }

        public override string ToString()
        {
            InternalCalls.MonoPointToString(ref this, out string result);
            return result;
        }
    }
}
