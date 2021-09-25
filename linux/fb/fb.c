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
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 56; j++) {
            int offset = i*(xres+pad) + 10*j;
            for (int k = 0; k < 10; k++) {
                fb[offset+k] = colors[j];
            }
        }
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

    //set resolution/dpi/color depth/.. in varInfo, then write it back
    // ioctl( fdScreen, FBIOPUT_VSCREENINFO, &varInfo );


    printf("%dx%dx%d\n", fbInfo.xres, fbInfo.yres, fbInfo.bits_per_pixel);
    printf("virtual: %dx%d\n", fbInfo.xres_virtual, fbInfo.yres_virtual);
    // reason for pad: does the stride have to be a multiple
    // of 128 or something else?
    long pad = 0;

    // check args to override pad
    if (argc > 1) {
        errno = 0;
        pad = strtol(argv[1], NULL, 10);
        if (errno || pad < 0 || pad > 4096) {
            perror("invalid value for pad");
            exit(1);
        }
    } else {
        if (fbInfo.xres % 256) {
            printf("you probably should provide a pad\n%s %d\n",
                   argv[0], fbInfo.xres % 256);
        }
        if (fbInfo.xres_virtual - fbInfo.xres) {
            printf("you probably should provide a pad\n%s %d\n",
                   argv[0], fbInfo.xres_virtual - fbInfo.xres);
        }
    }
    if (pad) {
        printf("using pad of %ld pixels\n", pad);
    }
    printf("%d x %d\n", fbInfo.xres, fbInfo.yres);

    long pagesize = sysconf(_SC_PAGE_SIZE);
    printf("pagesize: %ld\n", pagesize);


    int fd = open(FBDEV, O_RDWR);
    if (fd < 0) {
        perror(FBDEV);
        exit(1);
    }
    //get writable screen memory; 32bit color
    uint32_t length = 4 * (fbInfo.xres + pad) * fbInfo.yres;
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

    draw_colors(fb, fbInfo.xres, fbInfo.yres, pad);

    munmap(fb, length);

    return 0;
}
