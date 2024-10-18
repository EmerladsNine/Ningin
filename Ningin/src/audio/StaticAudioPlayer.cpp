#include "StaticAudioPlayer.h"
#include "portaudio.h"
#include "dr_mp3.h"
#include "stdlib.h"
#include "AudioData.h"
#include <string>
#include <thread>

bool StaticAudioPlayer::_MustStop = false;
static int audioCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    AudioData* data = (AudioData*)userData;
    float* out = (float*)outputBuffer;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
    unsigned long framesToPlay = (framesPerBuffer < framesLeft) ? framesPerBuffer : framesLeft;

    // Copy audio samples to output buffer
    for (unsigned long i = 0; i < framesToPlay; ++i) {
        for (int ch = 0; ch < data->channels; ++ch) {
            *out++ = data->samples[data->frameIndex * data->channels + ch];
        }
        data->frameIndex++;
    }

    // If we run out of frames, fill the rest of the buffer with silence
    for (unsigned long i = framesToPlay; i < framesPerBuffer; ++i) {
        for (int ch = 0; ch < data->channels; ++ch) {
            *out++ = 0.0f; // silence
        }
    }

    // End stream when all frames are played
    return (data->frameIndex < data->maxFrameIndex) ? paContinue : paComplete;
}

void StaticAudioPlayer::PlayAudio(const char* path)
{
    std::thread AudioThread(_PlayAudio,std::string(path));
    AudioThread.detach();
}


void StaticAudioPlayer::_PlayAudio(string path)
{
    _MustStop = false;

    drmp3 mp3;
    if (!drmp3_init_file(&mp3, path.c_str(), NULL)) {

        LogError("Failed to load MP3 file: " + std::string(path));
        return;
    }
    drmp3_uint64 totalPCMFrameCount = drmp3_get_pcm_frame_count(&mp3);
    drmp3_uint64 totalSampleCount = totalPCMFrameCount * mp3.channels;
    float* pSampleData = (float*)malloc((size_t)totalSampleCount * sizeof(float));
    if (pSampleData == NULL) {
        LogError("Failed to allocate memory for PCM data\n");
        drmp3_uninit(&mp3);
        return;
    }

    drmp3_uint64 samplesDecoded = drmp3_read_pcm_frames_f32(&mp3, totalPCMFrameCount, pSampleData);
    if (samplesDecoded > 0) {
        LogInfo("Successfully decoded PCM frames\n");
    }
    else {
        LogError("Failed to decode MP3\n");
    }

    drmp3_uninit(&mp3);

    // Set up audio data for PortAudio
    AudioData audioData;
    audioData.samples = pSampleData;
    audioData.frameIndex = 0;
    audioData.maxFrameIndex = (size_t)totalPCMFrameCount;
    audioData.channels = mp3.channels;

    // Initialize PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        LogError("PortAudio error: " + std::string(Pa_GetErrorText(err)));
        free(pSampleData);
        return;
    }

    // Open PortAudio stream
    PaStream* stream;
    err = Pa_OpenDefaultStream(&stream,
        0,                    // No input channels
        audioData.channels,    // Number of output channels
        paFloat32,             // Output sample format
        mp3.sampleRate,        // Sample rate
        256,                   // Frames per buffer
        audioCallback,         // Callback function
        &audioData);           // User data (our audio data)

    if (err != paNoError) {
        LogError("PortAudio error: " + std::string(Pa_GetErrorText(err)));
        Pa_Terminate();
        free(pSampleData);
        return;
    }

    // Start the audio stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        LogError("PortAudio error: " + std::string(Pa_GetErrorText(err)));
        Pa_Terminate();
        free(pSampleData);
        return;
    }

    // Wait for the stream to finish
    while (Pa_IsStreamActive(stream) == 1 && !StaticAudioPlayer::_MustStop) {
        Pa_Sleep(100); // Sleep 100ms while waiting for stream to finish
    }

    _MustStop = false;

    // Stop the stream
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    // Clean up
    free(pSampleData);
}

void StaticAudioPlayerStopAudio()
{
    StaticAudioPlayer::_MustStop = true;
}
