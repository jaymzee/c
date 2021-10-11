#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

/*
 * virtual address space of memory regions
 * demonstrate different ways to allocate blocks of memory
 *
 * compile with -static
 * run with setarch -R to disable address space randomization
 *
 * objdump -t | sort
 *
 * .text
 * .rodata
 * .data
 * .bss
 *
 */

int main(int argc, char *argv[])
{
    void *mptr, *pptr, *bptr;
    pid_t pid;

    pid = fork();

    bptr = sbrk(0);
    mptr = malloc(4096);
    // should be zero filled and can be used for IPC
    // with MAP_PRIVATE children's writes on the inherited mapping
    // are catered in copy-on-write manner
    // on systems without MAP_ANONYMOUS like BSD, use:
    //  fd = open("/dev/zero", O_RDWR);
    //  pptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    pptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    printf("main:   %p\n", main);
    printf("stack:  %p\n", &argc);
    printf("malloc: %p\n", mptr);
    printf("mmap:   %p\n", pptr);
    printf("brk:    %p\n", bptr);
}
