#pragma once

#include "../utils/Debug.h"
class StaticAudioPlayer
{
public:
	static void PlayAudio(const char* path);
	static bool _MustStop;
private:
	static void _PlayAudio(string path);
};
void StaticAudioPlayerStopAudio();