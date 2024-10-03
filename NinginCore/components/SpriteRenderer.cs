using System;

namespace NinginCore
{
    public class SpriteRenderer : Component
    {

        void SetTintingColor(ref Color color)
        {
            InternalCalls.SpriteSetTintingColor(this.data, ref color);
        }

        void SetUseTint(bool useTint)
        {
            InternalCalls.SpriteSetUseTint(this.data, useTint);
        }
    }
}
