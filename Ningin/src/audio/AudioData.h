#pragma once
typedef struct {
    float* samples;
    size_t frameIndex;    // Current frame index
    size_t maxFrameIndex; // Total frames in the sample
    int channels;         // Number of channels (1 = mono, 2 = stereo)
} AudioData;