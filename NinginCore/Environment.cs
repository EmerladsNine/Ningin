using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NinginCore
{
    public static class Environment
    {
        public static string GetGameDirectory()
        {
            InternalCalls.EnvironmentGetGameDirectory(out string GameDirectory);
            return GameDirectory;
        }
    }
}
