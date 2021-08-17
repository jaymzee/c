#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("stdin %d\n", STDIN_FILENO);
    printf("stdout %d\n", STDOUT_FILENO);
    printf("stderr %d\n", STDERR_FILENO);

    printf("stdin %d\n", fileno(stdin));
    printf("stdout %d\n", fileno(stdout));
    printf("stderr %d\n", fileno(stderr));
}
