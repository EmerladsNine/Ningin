using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NinginCore.input
{
    public static class KeyInput
    {
        public static bool IsKeyDown(KeyCode keyCode)
        {
            return InternalCalls.IsKeyDown((int)keyCode);
        }
    }
}
