#include "wavefmt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define PI 3.14159265358979323846

struct wavefmt fmt1 = {
    "RIFF", /* RIFF chunk tag */
    0,      /* file length minus 8 bytes */
    "WAVE", /* WAVE chunk tag */
    "fmt ", /* format chunk tag */
    16,     /* format chunk length */
    WAVEFMT_PCM,
    1,      /* no. of channels */
    8000,   /* sample rate */
    8000,   /* byte rate */
    1,      /* block align */
    8,      /* bits per sample */
    "data", /* data chunk tag */
    0       /* size of data */
}; /* overall size of header should be 44 bytes */

struct wavefmt fmt2 = {
    "RIFF", /* RIFF chunk tag */
    0,      /* file length minus 8 bytes */
    "WAVE", /* WAVE chunk tag */
    "fmt ", /* format chunk tag */
    16,     /* format chunk length */
    WAVEFMT_PCM,
    1,      /* no. of channels */
    44100,  /* sample rate */
    88200,  /* byte rate */
    2,      /* block align */
    16,     /* bits per sample */
    "data", /* data chunk tag */
    0       /* size of data */
}; /* overall size of header should be 44 bytes */

struct wavefmt fmt3 = {
    "RIFF", /* RIFF chunk tag */
    0,      /* file length minus 8 bytes */
    "WAVE", /* WAVE chunk tag */
    "fmt ", /* format chunk tag */
    16,     /* format chunk length */
    WAVEFMT_FLOAT,
    1,      /* no. of channels */
    44100,  /* sample rate */
    176400, /* byte rate */
    4,      /* block align */
    32,     /* bits per sample */
    "data", /* data chunk tag */
    0       /* size of data */
}; /* overall size of header should be 44 bytes */

int main()
{
    FILE *fp;
    double t, T, y;
    int n;
    uint8_t samp8;
    int16_t samp16;
    float samp32;

    fmt1.data_size = fmt1.samplerate * 1; /* one second */
    fmt1.riff_size = fmt1.data_size + 44 - 8;
    fp = fopen("mono-8bit-8khz.wav", "wb");
    wavefmt_write_header(&fmt1, fp);
    T = 1.0 / (double)fmt1.samplerate;
    t = 0.0;
    for (n = 0; n < fmt1.samplerate; n++) {
        y = cos(2 * PI * 1000 * t);
        /* scale and quantize (round) output sample */
        samp8 = 128.5 + 50.0 * y;
        fwrite(&samp8, 1, 1, fp);
        t += T;
    }
    fclose(fp);
    
    fmt2.data_size = fmt2.samplerate * 2; /* one second */
    fmt2.riff_size = fmt2.data_size + 44 - 8;
    fp = fopen("mono-16bit-44khz.wav", "wb");
    wavefmt_write_header(&fmt2, fp);
    T = 1.0 / (double)fmt2.samplerate;
    t = 0.0;
    for (n = 0; n < fmt2.samplerate; n++) {
        y = cos(2 * PI * 1000 * t);
        /* scale and quantize (round) output sample */
        samp16 = (int)(32768.5 + 15000.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fp);
        t += T;
    }
    fclose(fp);

    fmt3.data_size = fmt3.samplerate * 4; /* one second */
    fmt3.riff_size = fmt3.data_size + 44 - 8;
    fp = fopen("mono-float-44khz.wav", "wb");
    wavefmt_write_header(&fmt3, fp);
    T = 1.0 / (double)fmt3.samplerate;
    t = 0.0;
    for (n = 0; n < fmt3.samplerate; n++) {
        y = cos(2 * PI * 1000 * t);
        samp32 = 0.457 * y;
        fwrite(&samp32, 4, 1, fp);
        t += T;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
