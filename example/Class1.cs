using System;
using System.Threading;
using NinginCore;
using NinginCore.audio;
using NinginCore.input;

namespace example
{
    public class Class1 : Entity
    {
        TextRenderer spr;
        void Start()
        {
            var vec = new Vector2(-10, -60);
            var v2 = vec.Abs();
            Debug.LogInfo("Hi C#");
            Debug.LogInfo(v2.ToString());
            Debug.LogInfo(entityId.ToString());
            //spr = GetComponent<TextRenderer>();
//            throw new Exception("Testing EXCEPTIONS !!");
        }

        float time = 0f;
        bool is_playing = false;

        void Update(float deltatime)
        {
            time += deltatime;
            if (KeyInput.IsKeyDown(KeyCode.KEY_W))
            {
                transform.Position -= new Vector3(0, 50, 0) * deltatime;
            }
            else if (KeyInput.IsKeyDown(KeyCode.KEY_S))
            {
                transform.Position += new Vector3(0, 50, 0) * deltatime;
            }
            //Console.WriteLine(transform.ToString());
            if (KeyInput.IsKeyDown(KeyCode.KEY_A))
            {
                transform.Position -= new Vector3(50, 0, 0) * deltatime;
            }
            else if (KeyInput.IsKeyDown(KeyCode.KEY_D))
            {
                transform.Position += new Vector3(50, 0, 0) * deltatime;
            }

            if (KeyInput.IsKeyDown(KeyCode.KEY_ENTER))
            {
                if (is_playing)
                {
                    StaticAudioPlayer.StopAudio();
                    is_playing = false;
                }
                else
                {
                    string GameDirectory = NinginCore.Environment.GetGameDirectory();
                    StaticAudioPlayer.PlayAudio(GameDirectory + "/sample_song.mp3");
                    is_playing = true;
                }
                Thread.Sleep(1000);
            }

            // Cycle through colors by modifying RGB values based on time
            //uint red = (uint)(System.Math.Sin(time * 2) * 127 + 128);  // Oscillates between 0 and 255
            //uint green = (uint)(System.Math.Sin(time * 3) * 127 + 128); // Different frequency for green
            //uint blue = (uint)(System.Math.Sin(time * 4) * 127 + 128);  // Different frequency for blue
            //uint alpha = 255;  // Full opacity

            //spr.SetTextColor(Color.FromRGBA(red, green, blue, alpha));
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
