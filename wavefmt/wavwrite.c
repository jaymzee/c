#include "wavefmt.h"
#include <stdio.h>
#include <stdint.h>

struct wavefmt fmt1 = {
    "RIFF", /* RIFF chunk tag */
    40,     /* file length minus 8 bytes */
    "WAVE", /* WAVE chunk tag */
    "fmt ", /* format chunk tag */
    16,     /* format chunk length */
    1,      /* PCM */
    1,      /* no. of channels */
    8000,   /* sample rate */
    8000,   /* byte rate */
    1,      /* block align */
    8,      /* bits per sample */
    "data", /* data chunk tag */
    4       /* size of data */
}; /* overall size of header should be 44 bytes */
uint8_t data1[4] = {42, 43, 44, 45};

struct wavefmt fmt2 = {
    "RIFF", /* RIFF chunk tag */
    52,     /* file length minus 8 bytes */
    "WAVE", /* WAVE chunk tag */
    "fmt ", /* format chunk tag */
    16,     /* format chunk length */
    1,      /* PCM */
    2,      /* no. of channels */
    48000,  /* sample rate */
    192000, /* byte rate */
    4,      /* block align */
    16,     /* bits per sample */
    "data", /* data chunk tag */
    16      /* size of data */
}; /* overall size of header should be 44 bytes */
int16_t data2[8] = {0, 1, -1, 200, -200, 1000, -1000, 0};

int main()
{
    FILE *fp;

    fp = fopen("audio-mono-8bit-8khz.wav", "wb");
    wavefmt_write_header(&fmt1, fp);
    fwrite(data1, 1, 4, fp);
    fclose(fp);

    fp = fopen("audio-stereo-16bit-48khz.wav", "wb");
    wavefmt_write_header(&fmt2, fp);
    fwrite(data2, 2, 8, fp);
    fclose(fp);

    return 0;
}
