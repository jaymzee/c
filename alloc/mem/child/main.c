#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * demonstrate IPC using shared anonymous mappings
 *
 */

void show_memory(void)
{
    void *mptr, *pptr;

    mptr = malloc(4096);
    // should be zero filled and can be used for IPC
    // with MAP_PRIVATE children's writes on the inherited mapping
    // are catered in copy-on-write manner
    // on systems without MAP_ANONYMOUS like BSD, use:
    //  fd = open("/dev/zero", O_RDWR);
    //  pptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    pptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    printf(" stack:  %p\n", &mptr);
    printf(" malloc: %p\n", mptr);
    printf(" mmap:   %p\n", pptr);

    munmap(pptr, 4096);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    char *data;

    printf("program initialization\n");

    show_memory();
    data = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (data == MAP_FAILED) {
        perror("mmap shared");
        exit(1);
    }
    strcpy(data, "hello from parent!");

    pid = fork();

    if (pid > 0) {
        printf("parent: pid = %d\n", getpid());
        printf("parent: child pid = %d\n", pid);
        wait(NULL);
        printf("parent: shared data = %s\n", data);
    } else {
        printf("child: parent pid = %d\n", getppid());
        show_memory();
        printf("child: shared data = %s\n", data);
        printf("child: press enter to continue...\n");
        getchar();
        strcpy(data, "goodbye from child!");
        printf("child: terminating...\n");
        exit(0);
    }

    printf("parent: child has terminated\n");

    return 0;
}
