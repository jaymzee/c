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
#include <time.h>
#include <unistd.h>

#define FBDEV "/dev/fb0"
#define OMAPFB_WAITFORVSYNC_FRAME _IOWR('O', 70, unsigned int)

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

void query_fb_var(const char *device, struct fb_var_screeninfo *fbvar) {
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror(device);
        exit(1);
    }
    ioctl(fd, FBIOGET_VSCREENINFO, fbvar);
    close(fd);
}

void query_fb_fix(const char *device, struct fb_fix_screeninfo *fbfix) {
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror(device);
        exit(1);
    }
    ioctl(fd, FBIOGET_FSCREENINFO, fbfix);
    close(fd);
}

void vsync(int fd)
{
    int arg = 0;
    ioctl(fd, FBIO_WAITFORVSYNC, &arg);
}

void vsync2(int fd)
{
    unsigned int arg = 0;
    ioctl(fd, OMAPFB_WAITFORVSYNC_FRAME, &arg);
}

void microsleep(unsigned int usec) {
    struct timespec req, rem;

    unsigned int sec = usec / 1000000;
    usec -= sec * 1000000;
    req.tv_sec = sec;
    req.tv_nsec = usec * 1000;
    nanosleep(&req, &rem);
}

int main(int argc, char *argv[])
{
    struct fb_var_screeninfo fbvar;
    struct fb_fix_screeninfo fbfix;

    query_fb_var(FBDEV, &fbvar);
    query_fb_fix(FBDEV, &fbfix);

    // validate fbinfo
    if (!fbvar.xres || !fbvar.yres) {
        fprintf(stderr, "invalid framebuffer resolution\n");
        exit(1);
    }
    if (fbvar.bits_per_pixel != 32) {
        fprintf(stderr, "32 bpp expected\n");
        exit(1);
    }

    long pad = (fbfix.line_length / 4) - fbvar.xres;

    printf("fb-id: %s\n", fbfix.id);
    printf("fb-smem start/len: %lx %d\n", fbfix.smem_start, fbfix.smem_len);
    printf("fb-type: %d\n", fbfix.type);  // 0: packed pixels
    printf("fb-xpanstep: %d\n", fbfix.xpanstep);
    printf("fb-ypanstep: %d\n", fbfix.ypanstep);
    if (fbfix.visual & FB_VISUAL_TRUECOLOR) {
        printf("true color\n");
    }
    printf("fb-accel: %x\n", fbfix.accel);

    //set resolution/dpi/color depth/.. in varInfo, then write it back
    // ioctl( fdScreen, FBIOPUT_VSCREENINFO, &varInfo );

    printf("%dx%dx%d  ", fbvar.xres, fbvar.yres, fbvar.bits_per_pixel);
    printf("(%dx%d virtual)\n", fbvar.xres_virtual, fbvar.yres_virtual);

    int fd = open(FBDEV, O_RDWR);
    if (fd < 0) {
        perror(FBDEV);
        exit(1);
    }
    //get writable screen memory; 32bit color (4 bytes) and double buffer
    uint32_t length = 2 * 4 * (fbvar.xres + pad) * fbvar.yres;
    uint32_t *fb = mmap(NULL,
                        length,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        0);

    if (fb == MAP_FAILED) {
        printf("mmap fb failed\n");
        exit(1);
    }

    draw_colors(fb, fbvar.xres, fbvar.yres, pad);

    for (int i = 0; i < 128; i++) {
        microsleep(8000);
        fbvar.xoffset = i;
        ioctl(fd, FBIOPAN_DISPLAY, &fbvar);
    }

    sleep(1);

    fbvar.xoffset = 0;
    ioctl(fd, FBIOPAN_DISPLAY, &fbvar);

    munmap(fb, length);
    close(fd);

    return 0;
}
