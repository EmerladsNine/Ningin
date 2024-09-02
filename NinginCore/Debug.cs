using System.Runtime.CompilerServices;
namespace Ningin{
    public static class Debug{
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log_Error(string error);
    }
}