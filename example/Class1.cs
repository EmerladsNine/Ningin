using System;
using NinginCore;

namespace example
{
    public class Class1 : Entity
    {
        void Start()
        {
            var vec = new Vector2(-10, -60);
            var v2 = vec.Abs();
            Debug.LogInfo("Hi C#");
            Debug.LogInfo(v2.ToString());
            Debug.LogInfo(entityId.ToString());
            throw new Exception("Testing EXCEPTIONS !!");
        }
        // bool is_updated = false;
        float time = 0f;
        int nextsecond = 1;
        void Update(float deltatime)
        {
            time += deltatime;
            transform.Position = new Vector3(10, 50, 0) * deltatime;
            transform.Rotation = new Vector3(0, 0, 30) * deltatime;
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
