#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "font8x8_basic.h"

#define FBDEV "/dev/fb0"

void draw_colors(uint32_t *fb, uint32_t xres, uint32_t yres, uint32_t pad)
{
    // draw some color bars
    uint32_t colors[56] = {
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff,
        0xff0000, 0xff8000, 0xffff00, 0x00ff00, 0x00ffff, 0x0000ff, 0x8000ff
    };
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 56; j++) {
            int offset = i*(xres+pad) + 10*j;
            for (int k = 0; k < 10; k++) {
                fb[offset+k] = colors[j];
            }
        }
    }
}

// 32x16 font blocky (stretched 8x8 font)
void draw_text(uint32_t *fb, struct fb_var_screeninfo *fbinfo,
               char *str, int x, int y, int color)
{
    int stride = fbinfo->xres_virtual;
    for (int n = 0; str[n]; n++) {
        uint8_t c = str[n] & 0x7f; // strip off 8th bit
        for (int i = 0; i < 8; i++) {
            uint8_t d = font8x8_basic[c][i];
            for (int j = 0; j < 8; j++) {
                int offset = x + j*2 + (y+i*4)*stride;
                if (d & 1) {
                    fb[offset] = color;
                    fb[offset + 1] = color;
                    fb[offset + stride] = color;
                    fb[offset + stride + 1] = color;
                    fb[offset + 2*stride] = color;
                    fb[offset + 2*stride + 1] = color;
                    fb[offset + 3*stride] = color;
                    fb[offset + 3*stride + 1] = color;
                } else {
                    fb[offset] = 0;
                    fb[offset + 1] = 0;
                    fb[offset + stride] = 0;
                    fb[offset + stride + 1] = 0;
                    fb[offset + 2*stride] = 0;
                    fb[offset + 2*stride + 1] = 0;
                    fb[offset + 3*stride] = 0;
                    fb[offset + 3*stride + 1] = 0;
                }
                d = d >> 1;
            }
        }
        x += 16;
    }
}

void query_framebuffer(const char *device, struct fb_var_screeninfo *fbinfo) {
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror(device);
        exit(1);
    }
    ioctl(fd, FBIOGET_VSCREENINFO, fbinfo);
    close(fd);
}

int main(int argc, char *argv[])
{
    struct fb_var_screeninfo fbInfo;
    query_framebuffer(FBDEV, &fbInfo);

    // validate fbinfo
    if (!fbInfo.xres || !fbInfo.yres) {
        fprintf(stderr, "invalid framebuffer resolution\n");
        exit(1);
    }
    if (fbInfo.bits_per_pixel != 32) {
        fprintf(stderr, "32 bpp expected\n");
        exit(1);
    }

    int fd = open(FBDEV, O_RDWR);
    if (fd < 0) {
        perror(FBDEV);
        exit(1);
    }
    //get writable screen memory; 32bit color
    uint32_t length = 4 * fbInfo.xres_virtual * fbInfo.yres;
    uint32_t *fb = mmap(NULL,
                        length,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        0);

    if (fb == NULL) {
        printf("mmap fb failed\n");
        exit(1);
    }

    draw_text(fb, &fbInfo, "hello, world!", 0, 0, 0x00ff00);
    draw_text(fb, &fbInfo, "bye for now", 0, 32, 0xffff00);

    munmap(fb, length);

    return 0;
}
