#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    struct fb_var_screeninfo fbInfo;
    int fd = open( "/dev/fb0", O_RDWR );
    ioctl(fd, FBIOGET_VSCREENINFO, &fbInfo);

    printf("%dx%dx%d\n", fbInfo.xres, fbInfo.yres, fbInfo.bits_per_pixel);

    //set resolution/dpi/color depth/.. in varInfo, then write it back
    // ioctl( fdScreen, FBIOPUT_VSCREENINFO, &varInfo );

    if (fbInfo.bits_per_pixel != 32) {
        fprintf(stderr, "32 bpp expected\n");
        exit(1);
    }

    //get writable screen memory; 32bit color
    uint32_t *fb = mmap(0, fbInfo.xres * fbInfo.yres,
                        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < 100; i++) {
        fb[i] = 0xff0000;
    }

    return 0;
}
