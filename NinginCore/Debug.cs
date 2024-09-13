namespace NinginCore
{
    public static class Debug
    {
        public static void LogInfo(string message) => InternalCalls.DebugLogInfo(message);
        public static void LogWarning(string message) => InternalCalls.DebugLogWarning(message);
        public static void LogError(string message) => InternalCalls.DebugLogError(message);
    }
}
