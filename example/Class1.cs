using System;
using NinginCore;

namespace example
{
    public class Class1 : Entity
    {
        SpriteRenderer spr;
        void Start()
        {
            var vec = new Vector2(-10, -60);
            var v2 = vec.Abs();
            Debug.LogInfo("Hi C#");
            Debug.LogInfo(v2.ToString());
            Debug.LogInfo(entityId.ToString());
            spr = GetComponent<SpriteRenderer>();
            throw new Exception("Testing EXCEPTIONS !!");
        }
        // bool is_updated = false;
        float time = 0f;
        int nextsecond = 1;
        void Update(float deltatime)
        {
            time += deltatime;
            if(deltatime == 0)
            {
                Debug.LogInfo("HHUUHHH");
            }
            transform.Position += new Vector3(10, 50, 0) * deltatime;
            transform.Rotation += new Vector3(0, 0, 30) * deltatime;

            // Cycle through colors by modifying RGB values based on time
            uint red = (uint)(System.Math.Sin(time * 2) * 127 + 128);  // Oscillates between 0 and 255
            uint green = (uint)(System.Math.Sin(time * 3) * 127 + 128); // Different frequency for green
            uint blue = (uint)(System.Math.Sin(time * 4) * 127 + 128);  // Different frequency for blue
            uint alpha = 255;  // Full opacity

            spr.SetTintingColor(Color.FromRGBA(red, green, blue, alpha));
            if (time >= nextsecond)
            {
                Console.WriteLine(nextsecond);
                nextsecond++;
            }
        }

        bool is_lupdated = false;
        void Late_Update(float deltatime)
        {
            if (!is_lupdated)
            {
                Console.WriteLine("Hello In LAteeeeee Update WLak");
                is_lupdated = true;
            }
        }
    }
}
