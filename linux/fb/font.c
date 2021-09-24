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

void draw_text(uint32_t *fb, struct fb_var_screeninfo *fbinfo,
               char *str, int x, int y)
{
    for (int n = 0; str[n]; n++) {
        uint8_t c = str[n] & 0x7f; // strip off 8th bit
        for (int i = 0; i < 8; i++) {
            uint8_t d = font8x8_basic[c][i];
            for (int j = 0; j < 8; j++) {
                if (d & 1) {
                    fb[x + j + (y+i)*fbinfo->xres_virtual] = 0x00ff00;
                } else {
                    fb[x + j + (y+i)*fbinfo->xres_virtual] = 0x000000;
                }
                d = d >> 1;
            }
        }
        x += 8;
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
    int ypos = 0;
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

    if (argc > 1) {
        ypos = atoi(argv[1]);
    }

    long pad = fbInfo.xres_virtual - fbInfo.xres;
    long pagesize = sysconf(_SC_PAGE_SIZE);

    printf("pad: %ld\n", pad);

    int fd = open(FBDEV, O_RDWR);
    if (fd < 0) {
        perror(FBDEV);
        exit(1);
    }
    //get writable screen memory; 32bit color
    uint32_t *fb = mmap(NULL,
                        (fbInfo.xres + pad) * fbInfo.yres,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        4 * (fbInfo.xres + pad) * ypos);

    if (fb == NULL) {
        printf("mmap fb failed\n");
        exit(1);
    }

    draw_text(fb, &fbInfo, "hello, world!", 0, 0);

    munmap(fb, fbInfo.xres * fbInfo.yres);

    return 0;
}
