#ifndef WAVEFMT_H
#define WAVEFMT_H

/* RIFF WAVE file format */

#include "filter.h"
#include <stdint.h>
#include <stdio.h>

struct wavefmt {
    char     riff_tag[4];   /* RIFF chunk tag */
    uint32_t riff_size;     /* size of file (minus 8 bytes) */
    char     wave_tag[4];   /* WAVE chunk tag */
    char     fmt_tag[4];    /* 'fmt ' chunk tag */
    uint32_t fmt_size;      /* size of data format */
    uint16_t format;        /* format type 1-PCM, 3-FLOAT */
    uint16_t channels;      /* # of channels */
    uint32_t samplerate;    /* sample rate (fs) */
    uint32_t byterate;      /* byte rate = fs * channels * bitspersample / 8 */
    uint16_t blockalign;    /* block align = channels * bitspersample / 8 */
    uint16_t bitspersample; /* 8 bits or 16 bits */
    char     data_tag[4];   /* data chunk tag */
    uint32_t data_size;     /* size of data */
};

/* read the WAVEfmt RIFF header */
long wavefmt_read_header(struct wavefmt *fmt, const char *tag, FILE *fp);

/* write the WAVEfmt RIFF header */
long wavefmt_write_header(const struct wavefmt *fmt, FILE *fp);

/* print summary of the WAVEfmt RIFF header to stdout */
void wavefmt_print_header(const struct wavefmt *fmt);

/* dump a summary of the wav file to stdout */
int wavefmt_dump(const char *filename);

/* sample by sample process wav file */
int wavefmt_filter(const char *infile, const char *outfile,
                   filter_func *f, void *state, int format, double t);

#define WAVEFMT_PCM     1
#define WAVEFMT_FLOAT   3
#define WAVEFMT_ALAW    6
#define WAVEFMT_uLAW    7

#endif /* WAVEFMT_H */
