#include "wavefmt.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* helper for wavefmt_read_header */
static int read_fmt(struct wavefmt *fmt, char *fn, FILE *fp)
{
    int bytecount = 0;

    bytecount += fread(&fmt->fmt_size, 4, 1, fp) * 4;
    if (fmt->fmt_size >= 16) {
        bytecount += fread(&fmt->format, 2, 1, fp) * 2;
        bytecount += fread(&fmt->channels, 2, 1, fp) * 2;
        bytecount += fread(&fmt->samplerate, 4, 1, fp) * 4;
        bytecount += fread(&fmt->byterate, 4, 1, fp) * 4;
        bytecount += fread(&fmt->blockalign, 2, 1, fp) * 2;
        bytecount += fread(&fmt->bitspersample, 2, 1, fp) * 2;
    } else {
        fprintf(stderr,
                "%s: expected length of format >= 16 bytes, got %d\n",
                fn, fmt->fmt_size);
    }

    return bytecount;
}

/* helper for wavefmt_read_header */
static int read_data(struct wavefmt *fmt, char *fn, FILE *fp)
{
    int bytecount = 0;

    bytecount += fread(&fmt->data_size, 4, 1, fp) * 4;

    /* not going to actually read the data leaving the file pointer
       right at the beginning of it since this is the last chunk */

    return bytecount;
}

/*
 * wavefmt_read_header() - read the wavefmt RIFF header
 *
 * @fmt: pointer to the format header structure to fill
 * @fn:  filename (for better error messages)
 * @fp:  the file to read it from
 *
 * Return: offset of the start of wave data on a successful read of format
 *         0 otherwise
 */
long wavefmt_read_header(struct wavefmt *fmt, char *fn, FILE *fp)
{
    char tag[4];
    int size;
    int bytecount = 0;

    bytecount += fread(fmt->riff_tag, 1, 4, fp);
    if (strncmp(fmt->riff_tag, "RIFF", 4) != 0) {
        fprintf(stderr,
                "%s: expected chunk RIFF, but got %.4s\n",
                fn, fmt->riff_tag);
        goto fail;
    }
    bytecount += fread(&fmt->riff_size, 4, 1, fp) * 4;
    bytecount += fread(fmt->wave_tag, 1, 4, fp);
    if (strncmp(fmt->wave_tag, "WAVE", 4) != 0) {
        fprintf(stderr,
                "%s: expected chunk WAVE, but got %.4s\n",
                fn, fmt->wave_tag);
        goto fail;
    }

    while (!feof(fp)) {
        /* read chunk tag and chunk */
        bytecount += fread(tag, 1, 4, fp);
        if (strncmp(tag, "fmt ", 4) == 0) {
            strncpy(fmt->fmt_tag, tag, 4);
            bytecount += read_fmt(fmt, fn, fp);
        } else if (strncmp(tag, "data", 4) == 0) {
            strncpy(fmt->data_tag, tag, 4);
            bytecount += read_data(fmt, fn, fp);
            goto success;
        } else {
            /* ignore chunk */
            bytecount += fread(&size, 4, 1, fp) * 4;
            fseek(fp, size, SEEK_CUR);
        }
    }

success:
    return bytecount;   /* SUCCESS */
fail:
    return 0;   /* FAILURE - could not parse header properly */
}

/*
 * wavefmt_write_header() - write wavefmt RIFF header to file
 * @fmt: pointer to the format header struct to write
 *
 * Return: bytes written to file
 */
long wavefmt_write_header(struct wavefmt *fmt, FILE *fp)
{
    return fwrite(fmt, sizeof(*fmt), 1, fp);
}

/*
 * wavefmt_print_header() - print wavefmt RIFF header to stdout
 * @fmt: pointer to the format header structure to dump
 *
 * struct wavefmt fmt;
 * FILE fp = fopen("audio.wav", "rb");
 * long seek = wavefmt_read_header(&fmt, fp);
 * wavefmt_print_header(&fmt);
 * ...
 * ... process audio
 * ...
 */
void wavefmt_print_header(struct wavefmt *fmt)
{
    printf("file length: %u\n", fmt->riff_size + 8);
    printf("format: ");
    switch (fmt->format) {
    case 1:
        printf("PCM");
        break;
    case 3:
        printf("IEEE float");
        break;
    case 6:
        printf("8 bit A-law");
        break;
    case 7:
        printf("8 bit mu-law");
    default:
        printf("unknown %d", fmt->format);
        break;
    }
    printf("\n");
    printf("channels: %d\n", fmt->channels);
    printf("sample rate: %d\n", fmt->samplerate);
    printf("byte rate: %d\n", fmt->byterate);
    printf("block align: %d\n", fmt->blockalign);
    printf("bits per sample: %d\n", fmt->bitspersample);
    printf("data length (bytes): %d\n", fmt->data_size);
}

/*
 * wavefmt_dump() - print wavefmt RIFF header to stdout
 * @filename: file to dump
 *
 * convenience procedure for writing a wav file dump utility
 *
 * Return: 0 on successful read of RIFF header
          -2 could not open file
          -3 could not parse file
 */
int wavefmt_dump(char *filename)
{
    FILE *fp;
    struct wavefmt fmt;
    long data_seek_start;

    fp = fopen(filename, "rb");
    if (!fp) {
        perror(filename);
        return -2;
    }
    data_seek_start = wavefmt_read_header(&fmt, filename, fp);
    if (!data_seek_start) {
        /* wavefmt_read_header has already displayed a helpful error message */
        return -3;
    }
    fclose(fp);

    wavefmt_print_header(&fmt);
    printf("data seek start: 0x%08lx\n", data_seek_start);

    return 0;
}
