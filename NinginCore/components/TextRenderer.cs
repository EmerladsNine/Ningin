using System;

namespace NinginCore
{
    public class TextRenderer : Component
    {

        public void SetTextColor(Color color)
        {
            InternalCalls.TextSetTextColor(this.data, ref color);
        }

        public void SetText(string text)
        {
            InternalCalls.TextSetText(this.data, ref text);
        }

        public void SetFontSize(uint fontSize)
        {
            InternalCalls.TextSetFontSize(this.data, fontSize);
        }

        public void SetFont(string fontName)
        {
            InternalCalls.TextSetFont(this.data, ref fontName);
        }
    }
}
