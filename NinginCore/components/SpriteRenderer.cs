using System;

namespace NinginCore
{
    public class SpriteRenderer : Component
    {

        public void SetTintingColor(Color color)
        {
            InternalCalls.SpriteSetTintingColor(this.data, ref color);
        }

        public void SetUseTint(bool useTint)
        {
            InternalCalls.SpriteSetUseTint(this.data, useTint);
        }
    }
}
