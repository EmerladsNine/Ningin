using System;
using System.Collections;
using System.Runtime.InteropServices;

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
            InternalCalls.MonoTextSetText(this.data, text);
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
