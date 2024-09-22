namespace NinginCore
{
    public struct TextRenderer
    {
        void SetTextColor(Color color)
        {
            InternalCalls.TextSetTextColor(ref this, ref color);
        }

        void SetText(string text)
        {
            InternalCalls.TextSetText(ref this, ref text);
        }

        void SetFontSize(uint fontSize)
        {
            InternalCalls.TextSetFontSize(ref this, fontSize);
        }

        void SetFont(string fontName)
        {
            InternalCalls.TextSetFont(ref this, ref fontName);
        }
    }
}
