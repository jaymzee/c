/*
 * shared memory is the fastest IPC mechanism between two processes on the same host
 *
 * compile with:
 *
 *   gcc main.c -lrt
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHARED_MEM_NAME "sm-moo"

void panic(const char *msg);

int main(int argc, char *argv[])
{
    int fd_shm = shm_open(SHARED_MEM_NAME, O_RDWR | O_CREAT, 0660);
    if (fd_shm < 0) {
        panic("shm_open");
    }

    if (ftruncate(fd_shm, 4096) < 0) {
        panic("ftruncate");
    }

    char *sm_ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (sm_ptr == MAP_FAILED) {
        panic("mmap");
    }

    if (argc > 1) {
        strcpy(sm_ptr, argv[1]);
    } else {
        printf("press enter to quit\n");
        getchar();
        printf("shared-data: '%s'\n", sm_ptr);
    }

    //shm_unlink(SHARED_MEM_NAME);
}

void panic(const char *msg)
{
    perror(msg);
    exit(1);
}
