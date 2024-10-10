using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

public static class RustCalls
{
    [DllImport("./nsr.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern IntPtr getTokens(IntPtr file_input, out int out_size);
}


namespace NinginToolsExtension
{
    //[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    //public struct Identifier
    //{
    //    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 200)]
    //    public byte[] Value;

    //    public ulong Id;

    //    public Identifier()
    //    {
    //        Value = new byte[200];
    //        Id = 0;
    //    }
    //}
    [StructLayout(LayoutKind.Sequential)]
    public struct Pos
    {
        public UIntPtr line;  // C# equivalent of Rust's usize
        public UIntPtr column;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Token
    {
        public Pos pos;
        public IntPtr token_value;
        public IntPtr start;
        public IntPtr token_type;
        public IntPtr anotherRandData;
    }
}

