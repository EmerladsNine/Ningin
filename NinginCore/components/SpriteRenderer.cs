using System;

namespace NinginCore
{
    public class SpriteRenderer
    {
        internal IntPtr spriteRenderer;

        internal SpriteRenderer() {}

        void SetTintingColor(ref Color color)
        {
            InternalCalls.SpriteSetTintingColor(this.spriteRenderer, ref color);
        }

        void SetUseTint(bool useTint)
        {
            InternalCalls.SpriteSetUseTint(this.spriteRenderer, useTint);
        }
    }
}
