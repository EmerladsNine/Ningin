using System;

namespace NinginCore
{
    public class TextRenderer
    {
        internal IntPtr textRenderer;

        internal TextRenderer() { }

        void SetTextColor(Color color)
        {
            InternalCalls.TextSetTextColor(this.textRenderer, ref color);
        }

        void SetText(string text)
        {
            InternalCalls.TextSetText(this.textRenderer, ref text);
        }

        void SetFontSize(uint fontSize)
        {
            InternalCalls.TextSetFontSize(this.textRenderer, fontSize);
        }

        void SetFont(string fontName)
        {
            InternalCalls.TextSetFont(this.textRenderer, ref fontName);
        }
    }
}
