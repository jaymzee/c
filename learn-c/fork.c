#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    printf("program initialization\n");

    pid = fork();

    if (pid > 0) {
        printf("parent: pid = %d\n", getpid());
        printf("parent: child pid = %d\n", pid);
        wait(NULL);
    } else {
        printf("child: parent pid = %d\n", getppid());
        printf("child: press enter to continue...\n");
        getchar();
        printf("child: terminating...\n");
        exit(0);
    }

    printf("parent: child has terminated\n");

    return 0;
}
