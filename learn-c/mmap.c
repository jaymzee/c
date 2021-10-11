#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    const char *fname = "foo.bin";
    const int fd = open(fname, O_RDWR);
    char *p;

    if (fd < 0) {
        perror(fname);
        exit(1);
    }

    //p = mmap(NULL, 256, PROT_READ, MAP_PRIVATE, fd, 0);
    p = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    printf("%02X\n", 0xFF & p[0]);
    p[0] = 42;
    munmap(p, 256);
    close(fd);
}
