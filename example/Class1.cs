using System;
using Ningin;

namespace example
{
    public class Class1
    {
        void Start()
        {
            var vec = new Vector2(-10,-60);
            Console.WriteLine("Hello");
            throw new Exception("Testing EXCEPTIONS !!");
        }
        bool is_updated = false;
        float time = 0f;
        int nextsecond = 1;
        void Update(float deltatime)
        {
            time += deltatime;
            if(time >= nextsecond)
            {
                Console.WriteLine(nextsecond);
                nextsecond++;
            }
        }
        
        bool is_lupdated = false;
        void Late_Update(float deltatime)
        {
            if(!is_lupdated)
            {
                Console.WriteLine("Hello In LAteeeeee Update WLak");
                is_lupdated = true;
            }
        }
    }
}