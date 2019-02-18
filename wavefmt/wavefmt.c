#include "wavefmt.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* helper for wavefmt_read_header */
static long read_fmt(struct wavefmt *fmt, const char *fn, FILE *fp)
{
    long bytecount = 0;

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
                "%s: expected length of chunk fmt >= 16 bytes, got %d\n",
                fn, fmt->fmt_size);
    }
    if (bytecount < fmt->fmt_size + 4) {
        long skip = fmt->fmt_size + 4 - bytecount;
        fprintf(stderr, 
                "%s: skipping extra %ld bytes at end of chunk fmt\n", 
                fn, skip);
        fseek(fp, skip, SEEK_CUR);
        bytecount += skip;
    }

    return bytecount;
}

/* helper for wavefmt_read_header */
static long read_data(struct wavefmt *fmt, const char *fn, FILE *fp)
{
    long bytecount = 0;

    bytecount += fread(&fmt->data_size, 4, 1, fp) * 4;

    /* don't actually read the data.
       leave the file pointer right at the beginning of it
       since this is the last chunk */

    return bytecount;
}

/*
 * wavefmt_read_header() - read the wavefmt RIFF header
 * @fmt: pointer to the format header structure to fill
 * @fn:  filename (for better error messages)
 * @fp:  the file to read it from
 *
 * Return: offset of the start of wave data on a successful read of format
 *         0 otherwise
 */
long wavefmt_read_header(struct wavefmt *fmt, const char *fn, FILE *fp)
{
    long bytecount = 0;

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
        /* read chunk tag and the chunk */
        char chunktag[4];
        bytecount += fread(chunktag, 1, 4, fp);
        if (strncmp(chunktag, "fmt ", 4) == 0) {
            strncpy(fmt->fmt_tag, chunktag, 4);
            bytecount += read_fmt(fmt, fn, fp);
        } else if (strncmp(chunktag, "data", 4) == 0) {
            strncpy(fmt->data_tag, chunktag, 4);
            bytecount += read_data(fmt, fn, fp);
            goto success;
        } else {
            /* ignore chunk */
            uint32_t chunksize;
            fprintf(stderr, "%s: ignoring chunk %.4s\n", fn, chunktag);
            bytecount += fread(&chunksize, 4, 1, fp) * 4;
            fseek(fp, chunksize, SEEK_CUR);
            bytecount += chunksize;
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
long wavefmt_write_header(const struct wavefmt *fmt, FILE *fp)
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
void wavefmt_print_header(const struct wavefmt *fmt)
{
    printf("file length: %u\n", fmt->riff_size + 8);
    printf("format: ");
    switch (fmt->format) {
    case WAVEFMT_PCM:
        printf("PCM");
        break;
    case WAVEFMT_FLOAT:
        printf("IEEE float");
        break;
    case WAVEFMT_ALAW:
        printf("8 bit A-law");
        break;
    case WAVEFMT_uLAW:
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
int wavefmt_dump(const char *filename)
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

static double clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

static void filter_pcm2float(FILE *fpi, FILE *fpo, 
                             filter_func *f, void *state, 
                             uint32_t Nin, uint32_t Nout)
{
    float x, y;
    int16_t samp16;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&samp16, 2, 1, fpi);
        x = samp16 / 32767.0;
        y = clamp(f(x, state), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(x, state), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
}

static void filter_pcm2pcm(FILE *fpi, FILE *fpo, 
                           filter_func *f, void *state, 
                           uint32_t Nin, uint32_t Nout)
{
    float x, y;
    int16_t samp16;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&samp16, 2, 1, fpi);
        x = samp16 / 32767.0;
        y = clamp(f(x, state), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(x, state), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
}


static void filter_float2float(FILE *fpi, FILE *fpo, 
                               filter_func *f, void *state, 
                               uint32_t Nin, uint32_t Nout)
{
    float x, y;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&x, 4, 1, fpi);
        y = clamp(f(x, state), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(x, state), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
}

static void filter_float2pcm(FILE *fpi, FILE *fpo, 
                             filter_func *f, void *state, 
                             uint32_t Nin, uint32_t Nout)
{
    float x, y;
    int16_t samp16;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&x, 4, 1, fpi);
        y = clamp(f(x, state), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(x, state), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
}

/*
 * wavefmt_filter() - sample by sample filter
 * @infile: filename of input wav file
 * @outfile: filename of output wav file
 * @f: callback function for sample by sample processing
 * @state: state to pass to sample processing function
 * @format: WAVEFMT_FLOAT or WAVEFMT_PCM
 * @t: length of time to run filter
 *
 * signal process infile to outfile (float)
 * t = 0.0 will make the output the same length as the input
 *
 * Return: 0 on success
 *        -2 could not open file
 *        -3 could not parse file
 *        -4 unsupported file format
 */
int wavefmt_filter(const char *infile, const char *outfile, 
                   filter_func *f, void *state, int format, double t)
{
    FILE *fpi, *fpo;
    struct wavefmt fmti, fmto;
    long data_offset;
    unsigned int Nin, Nout;

    fpi = fopen(infile, "rb");
    if (!fpi) {
        perror(infile);
        return -2;
    }
    fpo = fopen(outfile, "wb");
    if (!fpo) {
        perror(outfile);
        return -2;
    }
    data_offset = wavefmt_read_header(&fmti, infile, fpi);
    if (!data_offset) {
        return -3;
    }
    if (fmti.channels != 1) {
        fprintf(stderr, "%s: number of channels must be 1\n", infile);
        return -4;
    }
    if (format != WAVEFMT_PCM && format != WAVEFMT_FLOAT) {
        fprintf(stderr, "unsupported output format %d\n", format);
        return -4;
    }

    fmto = fmti;
    Nin = fmti.data_size / fmti.blockalign;
    Nout = (t == 0.0) ? Nin : fmto.samplerate * t;
    fmto.format = format;
    fmto.fmt_size = 16;
    fmto.bitspersample = (format == WAVEFMT_FLOAT) ? 32 : 16;
    fmto.blockalign = (format == WAVEFMT_FLOAT) ? 4 : 2;
    fmto.byterate = fmto.blockalign * fmto.samplerate;
    fmto.data_size = Nout * fmto.blockalign;
    fmto.riff_size = fmto.data_size + 16 + 8 + 8 + 4;
    wavefmt_write_header(&fmto, fpo);
  
    if (fmti.format == WAVEFMT_PCM && fmti.bitspersample == 16) {
        if (format == WAVEFMT_FLOAT) 
            filter_pcm2float(fpi, fpo, f, state, Nin, Nout);
        else if (format == WAVEFMT_PCM)
            filter_pcm2pcm(fpi, fpo, f, state, Nin, Nout);
    } else if (fmti.format == WAVEFMT_FLOAT && fmti.bitspersample == 32) {
        if (format == WAVEFMT_FLOAT) 
            filter_float2float(fpi, fpo, f, state, Nin, Nout);
        else if (format == WAVEFMT_PCM)
            filter_float2pcm(fpi, fpo, f, state, Nin, Nout);
    } else {
        fprintf(stderr, "%s: unsupported format\n", infile);
        return -4;
    }

    fclose(fpi);
    fclose(fpo);

    return 0;
}
