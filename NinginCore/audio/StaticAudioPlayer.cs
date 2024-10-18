using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NinginCore.audio
{
    public static class StaticAudioPlayer
    {
        public static void PlayAudio(string path)
        {
            InternalCalls.StaticAudioPlayerPlayAudio(path);
        }

        public static void StopAudio()
        {
            InternalCalls.StaticAudioPlayerStopAudio();
        }
    }
}
