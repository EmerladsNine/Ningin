namespace NinginCore
{
    public struct SpriteRenderer
    {
        void SetTintingColor(ref Color color)
        {
            InternalCalls.SpriteSetTintingColor(ref this, ref color);
        }

        void SetUseTint(bool useTint)
        {
            InternalCalls.SpriteSetUseTint(ref this, useTint);
        }
    }
}
