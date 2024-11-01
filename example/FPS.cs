using NinginCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace example
{
    public class FPS : Entity
    {
        TextRenderer textRenderer;
        void Start()
        {
            Debug.LogWarning("Heyyy");
            textRenderer = GetComponent<TextRenderer>();
        }

        uint frames = 0;
        float time = 0f;
        uint nextsecond = 1;
        void Update(float deltatime)
        {
            time += deltatime;
            frames++;
            if (time >= nextsecond)
            {
                textRenderer.SetText("[FPS] : " + frames);
                frames = 0;
                nextsecond = (uint)time + 1;
            }
        }
    }
}
